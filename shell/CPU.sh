#!/bin/bash 
DATE=`date +"%Y-%m-%d__%H:%M:%S"`
START_IDEL=`cat /proc/stat | head -n 1| cut -d " " -f 6`
START_SUM=`cat /proc/stat | head -n 1 | tr -s "a-z" "0" | tr -s " " "+" | bc`
sleep 0.5
END_IDEL=`cat /proc/stat | head -n 1 | cut -d " " -f 6`
END_SUM=`cat /proc/stat | head -n 1 | tr -s "a-z" "0" | tr -s " " "+" | bc`
PREC=`echo "scale=2;(1-($END_IDEL-$START_IDEL)/($END_SUM-$START_SUM))*100"|bc`
load=(`uptime | awk '{printf("%s %s %s",$8,$9,$10);}'`)
echo $DATE ${load[0]} ${load[1]} ${load[2]} $PREC



