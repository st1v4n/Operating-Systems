#Изведете всички обикновени ("regular") файлове, които само преките поддиректории на /etc съдържат
find -mindepth 2 -maxdepth 2 /etc -type f
