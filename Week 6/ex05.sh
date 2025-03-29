#!/bin/bash
#Да се напише shell скрипт, който намира броя на изпълнимите файлове в PATH.
#Hint: Предполага се, че няма спейсове в имената на директориите
#Hint2: Ако все пак искаме да се справим с този случай, да се разгледа IFS променливата и констуркцията while read -d

#!/bin/bash
   read -p "Enter path: " newpath
   count=0
   for file in $(find ${newpath} -mindepth 1 -type f 2>/dev/null) ; do
        if [[ -x "${file}" ]] ; then
        count=$(( count + 1))
        fi
   done
  
   echo "Number of executable files: ${count}"
