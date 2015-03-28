## this command line runs fibonacci encoding on sequential numbers from 1 to 1100000, and decodes them again. Finally it performs a delta on the decoded data.
#(((yes | nl -p -w 7 | awk '{print $1}' | head -n 1100000 | fib_coding | tee /dev/fd/2 | fib_decoding | awk 'BEGIN{var=0} {print $1-var " -- ("$1" - "var") " $0; var=$1}' > /dev/fd/3) 2>&1) > fib_encoded.log) 3>&1

## this command line runs 32-bit encoding on sequential numbers from 1 to 1100000
#yes | nl -p -w 7 | awk '{print $1}' | head -n 1100000 | 32bit_coding > 32bit_encoded.log

## this command line runs both fibonacci and 32-bit encoding on sequential numbers from 1 to 1100000 and shows the generated files.
((yes | nl -p -w 7 | awk '{print $1}' | head -n 100000000 | tee /dev/fd/3 | 32bit_coding > 32bit_encoded.log) 3>&1 ) | fib_coding > fib_encoded.log && ls -l | grep encoded
