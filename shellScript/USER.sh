#!/bin/bash 
USER_NUM=`cat /etc/passwd | tr ":" " " |awk -v cnt=0 '{if($3 >= 1000){cnt+=1;}} END{print cnt}';`

