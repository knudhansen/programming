(((yes | nl -p -w 7 | awk '{print $1}' | head -n 1100000 | coding | tee /dev/fd/2 | decoding | awk 'BEGIN{var=0} {print $1-var " -- ("$1" - "var") " $0; var=$1}' > /dev/fd/3) 2>&1) > encoded.log) 3>&1
