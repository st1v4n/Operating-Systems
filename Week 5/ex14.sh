#Намерете броя на уникалните символи, използвани в имената на потребителите от
#/etc/passwd.

cat /etc/passwd | cut -d ':' -f 5 | grep -o '.' | sort | uniq | wc -l
