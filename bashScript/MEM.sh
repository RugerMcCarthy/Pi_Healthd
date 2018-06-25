#!/bin/bash 
#This is MEMORY information


function Usage() {
    echo "Usage: $0 DyAver"
}

#if [[ $# -lt 1 ]]; then 
#    Usage
#    exit
#fi
#OldAver=$1;
DATE=`date +"%Y-%m-%d__%H:%M:%S"`
MEMVAL=(`free -m | head -n 2 | tail -n 1 | awk '{printf("%s %s %.2f",$2, $3, $3*100/$2);}'`)
#NewAver=`echo "scale=2;${MEMVAL[2]}*0.8+${OldAver}*0.2"|bc`
echo $DATE Total = ${MEMVAL[0]}, Used = ${MEMVAL[1]}, Occupy Rate = ${MEMVAL[2]}% #, NewAver = $NewAver%
