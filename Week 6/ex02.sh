#!/bin/bash
#Да се напише shell скрипт, който приема точно един параметър и проверява дали подаденият му параметър
#се състои само от букви и цифри.

 #!/bin/bash
if [[ ${#} -ne 1 ]] ; then
       echo "invalid number of arguments! Expected: 1"
       exit 1
fi
if [[ ! ${1} =~ ^[0-9a-zA-Z]+$ ]] ; then
       echo "invalid argument!"
       exit 2
fi
 
 echo " ${1} is a valid argument!"
