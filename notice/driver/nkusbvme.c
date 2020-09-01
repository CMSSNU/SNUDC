/*
 * NoticeKorea NKUSBVME USB/VME Interface board driver - 1.0.1
 *
 * Author : H.J. Kim (hongjoo@knu.ac.kr) Sept 1996
 * 
 * Author : E. Milman (milman.evgeniy@gmail.com)
 *              <Kyungpook National University> Jan 2012
 *
 * Based on rio500.c by Cesar Miquel 
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 *
 *   TODO :
 *   Current device driver does not support multiple device at the same time
 *   It will be updated for multiple device support later.
 *   
 * Changelog:
 *  1) Oct 17 2006 
 *  file_operations usb_nkusbvme_fops = {
 *   //	.owner =	THIS_MODULE,  <-commented out because Fedora 5 
 *                                      does not recognize .owner field
 * 
 *  2) Jan 19 2012 (Driver version 1.0.1)
 *      a) info() calls have been removed. This function is not suppordet on new 
 *                                               kernel versions
 *      b) file_operations usb_nkusbvme_fops = {
 *             -- .ioctl = ioctl_nkusbvme <- .ioctl has been changed to .unlocked_ioctl.
 *                                              .ioctl is depricated.
 *             ++ .unlocked_ioctl = unlocked_ioctl_nkusbvme
 *             -- static int ioctl_nkusbvme(struct file *file, unsigned int cmd, unsigned long arg) {             
 *             ++ static long unlocked_ioctl_nkusbvme(struct file *file, unsigned int cmd, unsigned long arg) {
 * 
 *      c) -- #include <linux/smp_lock.h>  <- this file has been removed from last version kernel.
 * 
 *      d) --init_MUTEX(&(nkusbvme->lock)); <- init_MUTEX is not supported anymore
 *         ++sema_init(&(nkusbvme->lock), 1); <- sema_init() is used instead of  init_MUTEX 
 *         
 */

#undef DEBUG  

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/random.h>
#include <linux/poll.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/usb.h>
#include <linux/wait.h>
#include <linux/version.h>

/*
 * Version Information
 */

#define DRIVER_VERSION "v1.0.1"
#define DRIVER_AUTHOR "H.J. Kim <hongjoo@knu.ac.kr>, E. Milman <milman.evgeniy@gmail.com>"
#define DRIVER_DESC " nkusbvme : NoticeKorea USB/VME interface board driver"

/* Get a minor range for your devices from the usb maintainer */
#define NKUSBVME_MINOR	190

/* we can have up to this number of devices plugged in at once */
#define MAX_DEVICES	10

/* stall/wait timeout for nkusbvme */
#define NAK_TIMEOUT (HZ)

#define IBUF_SIZE 0x10000   	/* 64 kbytes */

/* Size of the nkusbvme buffer */
#define OBUF_SIZE 0x1000        /* 64 kbytes */

/* FX2 Notice Korea USB-VME interface module vendor id & product id */
#define USB_NKUSBVME_VENDOR_ID	0x547
#define USB_NKUSBVME_PRODUCT_ID	0x1095   //changed from 0x1095 for temporary

/* endpoint for in & out for nkusbvme */
#define NKUSBVME_ENDPOINT_IN_ID  0x82 	
#define NKUSBVME_ENDPOINT_OUT_ID 0x06	

//

struct nkusbvme_usb_data {
    struct usb_device *nkusbvme_dev; /* init: probe_nkusbvme */
    unsigned int ifnum; /* Interface number of the USB device */
    int isopen; /* nz if open */
    int present; /* Device is present on the bus */
    char *obuf, *ibuf; /* transfer buffers */
    char bulk_in_ep, bulk_out_ep; /* Endpoint assignments */
    wait_queue_head_t wait_q; /* for timeouts */
    struct semaphore lock; /* general race avoidance */
};

static struct nkusbvme_usb_data nkusbvme_instance;

static int open_nkusbvme(struct inode *inode, struct file *file) {
    struct nkusbvme_usb_data *nkusbvme = &nkusbvme_instance;
    down(&(nkusbvme->lock));
    if (nkusbvme->isopen || !nkusbvme->present) {
        up(&(nkusbvme->lock));
        return -EBUSY;
    }
    nkusbvme->isopen = 1;
    init_waitqueue_head(&nkusbvme->wait_q);
    up(&(nkusbvme->lock));
    return 0;
}

static int close_nkusbvme(struct inode *inode, struct file *file) {
    struct nkusbvme_usb_data *nkusbvme = &nkusbvme_instance;
    nkusbvme->isopen = 0;
    return 0;
}

static ssize_t write_nkusbvme(struct file *file, const char __user *buffer, size_t count, loff_t * ppos) {
    DEFINE_WAIT(wait);
    struct nkusbvme_usb_data *nkusbvme = &nkusbvme_instance;

    unsigned long copy_size;
    unsigned long bytes_written = 0;
    unsigned int partial;

    int result = 0;
    int maxretry;
    int errn = 0;

    down(&(nkusbvme->lock));
    /* Sanity check to make sure nkusbvme is connected, powered, etc */
    if (nkusbvme == NULL ||
            nkusbvme->present == 0 ||
            nkusbvme->nkusbvme_dev == NULL) {
        up(&(nkusbvme->lock));
        return -ENODEV;
    }
    do {
        unsigned long thistime;
        char *obuf = nkusbvme->obuf;

        thistime = copy_size =
                (count >= OBUF_SIZE) ? OBUF_SIZE : count;
        if (copy_from_user(nkusbvme->obuf, buffer, copy_size)) {
            errn = -EFAULT;
            goto error;
        }
        maxretry = 5;
        while (thistime) {
            if (!nkusbvme->nkusbvme_dev) {
                errn = -ENODEV;
                goto error;
            }
            if (signal_pending(current)) {
                up(&(nkusbvme->lock));
                return bytes_written ? bytes_written : -EINTR;
            }

            result = usb_bulk_msg(nkusbvme->nkusbvme_dev,
                    usb_sndbulkpipe(nkusbvme->nkusbvme_dev, NKUSBVME_ENDPOINT_OUT_ID), obuf, thistime, &partial, 5000);

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
//            dbg("write stats: result:%d thistime:%lu partial:%u",
//                    result, thistime, partial);
#else
            pr_debug("%s write stats: result:%d thistime:%lu partial:%u",
                    __func__, result, thistime, partial);
#endif
            if (result == -ETIMEDOUT) { /* NAK - so hold for a while */
                if (!maxretry--) {
                    errn = -ETIME;
                    goto error;
                }
                prepare_to_wait(&nkusbvme->wait_q, &wait, TASK_INTERRUPTIBLE);
                schedule_timeout(NAK_TIMEOUT);
                finish_wait(&nkusbvme->wait_q, &wait);
                continue;
            } else if (!result && partial) {
                obuf += partial;
                thistime -= partial;
            } else
                break;
        };
        if (result) {
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
//            err("Write Whoops - %x", result);
#else
            pr_err("Write Whoops - %x", result);
#endif
            errn = -EIO;
            goto error;
        }
        bytes_written += copy_size;
        count -= copy_size;
        buffer += copy_size;
    } while (count > 0);

    up(&(nkusbvme->lock));

    return bytes_written ? bytes_written : -EIO;

error:
    up(&(nkusbvme->lock));
    return errn;
}

static ssize_t read_nkusbvme(struct file *file, char __user *buffer, size_t count, loff_t * ppos) {
    DEFINE_WAIT(wait);
    struct nkusbvme_usb_data *nkusbvme = &nkusbvme_instance;
    ssize_t read_count;
    unsigned int partial;
    int this_read;
    int result;
    int maxretry = 10;
    char *ibuf;

    down(&(nkusbvme->lock));
    /* Sanity check to make sure nkusbvme is connected, powered, etc */
    if (nkusbvme == NULL ||
            nkusbvme->present == 0 ||
            nkusbvme->nkusbvme_dev == NULL) {
        up(&(nkusbvme->lock));
        return -ENODEV;
    }

    ibuf = nkusbvme->ibuf;

    read_count = 0;


    while (count > 0) {
        if (signal_pending(current)) {
            up(&(nkusbvme->lock));
            return read_count ? read_count : -EINTR;
        }
        if (!nkusbvme->nkusbvme_dev) {
            up(&(nkusbvme->lock));
            return -ENODEV;
        }
        this_read = (count >= IBUF_SIZE) ? IBUF_SIZE : count;

        result = usb_bulk_msg(nkusbvme->nkusbvme_dev,
                usb_rcvbulkpipe(nkusbvme->nkusbvme_dev, NKUSBVME_ENDPOINT_IN_ID),

                ibuf, this_read, &partial,
                8000);

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
//        dbg("read stats: result:%d this_read:%u partial:%u",
//                result, this_read, partial);
#else
        pr_debug("%s read stats: result:%d this_read:%u partial:%u",
                __func__, result, this_read, partial);
#endif

        if (partial) {
            count = this_read = partial;
        } else if (result == -ETIMEDOUT || result == 15) {
            if (!maxretry--) {
                up(&(nkusbvme->lock));
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
//                err("read_nkusbvme: maxretry timeout");
#else
                pr_err("read_nkusbvme: maxretry timeout");
#endif
                return -ETIME;
            }
            prepare_to_wait(&nkusbvme->wait_q, &wait, TASK_INTERRUPTIBLE);
            schedule_timeout(NAK_TIMEOUT);
            finish_wait(&nkusbvme->wait_q, &wait);
            continue;
        } else if (result != -EREMOTEIO) {
            up(&(nkusbvme->lock));
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
//            err("Read Whoops - result:%u partial:%u this_read:%u",
//                    result, partial, this_read);
#else
            pr_err("Read Whoops - result:%u partial:%u this_read:%u",
                    result, partial, this_read);
#endif
            return -EIO;
        } else {
            up(&(nkusbvme->lock));
            return (0);
        }

        if (this_read) {
            if (copy_to_user(buffer, ibuf, this_read)) {
                up(&(nkusbvme->lock));
                return -EFAULT;
            }
            count -= this_read;
            read_count += this_read;
            buffer += this_read;
        }
    }
    up(&(nkusbvme->lock));
    return read_count;
}

static long unlocked_ioctl_nkusbvme(struct file *file, unsigned int cmd, unsigned long arg) {
    return 0;
}


static struct file_operations usb_nkusbvme_fops = {
    //.owner = THIS_MODULE,
    .read = read_nkusbvme,
    .write = write_nkusbvme,
    .unlocked_ioctl = unlocked_ioctl_nkusbvme,
    .open = open_nkusbvme,
    .release = close_nkusbvme,
};

static struct usb_class_driver usb_nkusbvme_class = {
    .name = "nkusbvme%d",
    .fops = &usb_nkusbvme_fops,
    .minor_base = NKUSBVME_MINOR,
};

static int probe_nkusbvme(struct usb_interface *intf, const struct usb_device_id *id) {
    struct usb_device *dev = interface_to_usbdev(intf);
    struct nkusbvme_usb_data *nkusbvme = &nkusbvme_instance;
    int retval;
    // max device is 10
    if (dev->devnum > (NKUSBVME_MINOR + MAX_DEVICES)) {
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
//        err("Max devices > 10 ");
#else
        pr_err("Max devices > 10 ");
#endif

        return -ENOMEM;
    }

    retval = usb_register_dev(intf, &usb_nkusbvme_class);
    if (retval) {
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
//        err("Not able to get a minor for this device.");
#else
        pr_err("Not able to get a minor for this device.");
#endif
        return -ENOMEM;
    }

    nkusbvme->nkusbvme_dev = dev;

    if (!(nkusbvme->obuf = (char *) kmalloc(OBUF_SIZE, GFP_KERNEL))) {
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
//        err("probe_nkusbvme: Not enough memory for the output buffer");
#else
        pr_err("probe_nkusbvme: Not enough memory for the output buffer");
#endif
        usb_deregister_dev(intf, &usb_nkusbvme_class);
        return -ENOMEM;
    }
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
//    dbg("probe_nkusbvme: obuf address:%p", nkusbvme->obuf);
#else
    pr_debug("%s probe_nkusbvme: obuf address:%p", __func__, nkusbvme->obuf);
#endif

    if (!(nkusbvme->ibuf = (char *) kmalloc(IBUF_SIZE, GFP_KERNEL))) {
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
//        err("probe_nkusbvme: Not enough memory for the input buffer");
#else
        pr_err("probe_nkusbvme: Not enough memory for the input buffer");
#endif
        usb_deregister_dev(intf, &usb_nkusbvme_class);
        kfree(nkusbvme->obuf);
        return -ENOMEM;
    }
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
//    dbg("probe_nkusbvme: ibuf address:%p", nkusbvme->ibuf);
#else
    pr_debug("%s probe_nkusbvme: ibuf address:%p", __func__, nkusbvme->ibuf);
#endif
    sema_init(&(nkusbvme->lock), 1);
    usb_set_intfdata(intf, nkusbvme);
    nkusbvme->present = 1;

    return 0;
}

static void disconnect_nkusbvme(struct usb_interface *intf) {
    struct nkusbvme_usb_data *nkusbvme = usb_get_intfdata(intf);

    usb_set_intfdata(intf, NULL);
    if (nkusbvme) {
        usb_deregister_dev(intf, &usb_nkusbvme_class);

        down(&(nkusbvme->lock));
        if (nkusbvme->isopen) {
            nkusbvme->isopen = 0;
            /* better let it finish - the release will do whats needed */
            nkusbvme->nkusbvme_dev = NULL;
            up(&(nkusbvme->lock));
            return;
        }
        kfree(nkusbvme->ibuf);
        kfree(nkusbvme->obuf);
        nkusbvme->present = 0;
        up(&(nkusbvme->lock));
    }
}


static struct usb_device_id nkusbvme_table [] = {
    { USB_DEVICE(USB_NKUSBVME_VENDOR_ID, USB_NKUSBVME_PRODUCT_ID)}, /* vender id and product id for FX2 chip of NoticeKorea USB/VME */
    {}
};

MODULE_DEVICE_TABLE(usb, nkusbvme_table);

static struct usb_driver nkusbvme_driver = {
    //	.owner =	THIS_MODULE,
    .name = "nkusbvme",
    .probe = probe_nkusbvme,
    .disconnect = disconnect_nkusbvme,
    .id_table = nkusbvme_table,
};

static int __init usb_nkusbvme_init(void) {
    int retval;
    retval = usb_register(&nkusbvme_driver);
    return retval;
}

static void __exit usb_nkusbvme_cleanup(void) {
    struct nkusbvme_usb_data *nkusbvme = &nkusbvme_instance;
    nkusbvme->present = 0;
    usb_deregister(&nkusbvme_driver);
}

module_init(usb_nkusbvme_init);
module_exit(usb_nkusbvme_cleanup);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
