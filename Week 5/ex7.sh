#Намерете само Group ID-то си от файлa /etc/passwd.

cat etc/passwd  | grep "$(whoami)" | cut -d ':' -f 4
