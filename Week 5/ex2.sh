#Намерете имената на топ 5 файловете в текущата директория с най-много hardlinks.

find . -maxdepth 1 -type f -printf '%n:%f\n' | sort -t ':' -k 1 -n -r | head -5 | cut -d ':' -f 2 
