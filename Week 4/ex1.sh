#Сортирайте /etc/passwd лексикографски по поле UserID.

cat /etc/passwd | sort -t ':' -k 3
