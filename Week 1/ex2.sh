# Направете директория practice-test в home директорията ви. Вътре направете директория test1. Можете ли да направите тези две неща наведнъж? Разгледайте нужната man страница. След това създайте празен файл вътре, който да се казва test.txt, преместете го в practice-test чрез релативни пътища.

mkdir ~/practice-test
cd ~/practice-test
mkdir test1
cd test1
touch test1.txt
mv test1.txt ../test1.txt
