#!/bin/bash
#Да се напише shell скрипт, който приканва потребителя да въведе низ - потребителско име на потребител от
#системата - след което извежда на стандартния изход колко активни сесии има потребителят в момента.

 #!/bin/bash
 read -p "Enter an username: " username
 echo "Number of active sessions: $(who | grep "${username}" | wc -l)"
