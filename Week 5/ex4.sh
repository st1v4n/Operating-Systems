#За всяка група от /etc/group изпишете "Hello, <група>", като ако това е вашата група, напишете "Hello, <група> - I am here!".

cat /etc/group | cut -d ':' -f 3 | uniq | xargs -I "X" echo "Hello, X - I am here!"
