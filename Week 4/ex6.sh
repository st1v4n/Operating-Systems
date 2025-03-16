#Изведете броя на байтовете в /etc/passwd.
#Изведете броя на символите в /etc/passwd.
#Изведете броя на редовете  в /etc/passwd.

cat /etc/passwd | wc -c
cat /etc/passwd | wc -m
cat /etc/passwd | wc -l
