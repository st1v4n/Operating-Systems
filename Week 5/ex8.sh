#Колко файлове в /bin са 'shell script'-oве?

find /bin -maxdepth 1 | xargs -I "X" cat X | grep "#!/bin/" | wc -l
