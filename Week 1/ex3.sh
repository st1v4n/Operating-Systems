#Създайте директорията practice/01 във вашата home директория.
#Създайте 3 файла в нея - f1, f2, f3.
#Копирайте файловете f1, f2, f3 от директорията practice/01/ в директория dir1, намираща се във вашата home директория. Ако нямате такава, създайте я.

mkdir -p ~/practice/01
cd ~/practice/01
touch f1 f2 f3
mkdir ~/dir1
cp f1 ~/dir1/f1
cp f2 ~/dir1/f2
cp f3 ~/dir1/f3
