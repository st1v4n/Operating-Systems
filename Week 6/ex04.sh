#!/bin/bash

#Да се напише shell скрипт, който приканва потребителя да въведе пълното име на директория и извежда на стандартния
#изход подходящо съобщение за броя на всички файлове и всички директории в нея.
#!/bin/bash
   read -p "Enter a directory name: " dirname
   if [[ ! -d ${dirname} ]] ; then
       echo "${dirname} is not a directory!"
       exit 1
   fi
   echo "Number of files: $(find ${dirname} -mindepth 1 -maxdepth 1 -type f | wc -l
   echo "Number of dirs: $(find ${dirname}  -mindepth 1 -maxdepth 1 -type d | wc -l

