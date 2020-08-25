#!/bin/sh

if ( cp -f ./nkusbvme.ko /lib/modules/`uname -r`/kernel/drivers/usb/misc ) then
	echo "Installed"
else
	echo "Installation Failed"
fi

/sbin/depmod -a
/sbin/modprobe nkusbvme

DIST=$(cat /etc/issue | head -1 | awk '{print $1}')

#Ubuntu Linux
if [ "$DIST" = "Ubuntu" ] 
then
    if(grep "nkusbvme" /etc/modules >>/dev/null) then
      echo "modprobe nkusbvme exist in modules"
    else 
      echo nkusbvme >> /etc/modules 
      echo "modprobe nkusbvme copyed into /etc/modules"
    fi

else

#Fedora or Scientific Linux series
  if(grep "modprobe nkusbvme" /etc/rc.d/rc.local >>/dev/null) then
   echo "modprobe nkusbvme exist in /etc/rc.d/rc.local"
  else 
   echo modprobe nkusbvme >> /etc/rc.d/rc.local 
   echo "modprobe nkusbvme copyed into /etc/rc.d/rc.local"
  fi

fi

