root -l -b <<EOF
.L src/SNUDC.C
SNUDC t
t.Loop()
.q
EOF

#scp -r ./plots/* suoh@147.47.242.44:/home/suoh/Dropbox/SNUDC/plots
