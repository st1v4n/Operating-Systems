#Запазете само потребителските имена от /etc/passwd във файл users във вашата home директория.

touch users
cat /etc/passwd | cut -d ':' -f 1 1>users
