#Отпечатайте потребителските имена и техните home директории от /etc/passwd.

cat /etc/passwd | cut -d ':' -f 5,6 | tr ':' ' ' | tr ',' ' ' | tr -s ' '
