#!/bin/bash
DATE=`date -u +"%Y-%m-%d__%H:%M:%S"`
PIDNUM=(`cut -d: -f 3 /etc/passwd | sort -n | head -n -1 | wc -l`)
PID=(`cut -d: -f 3 /etc/passwd | sort -n | head -n -1`)
for ((i=0; i<1000;++i));do
    if [[ ${PID[$i]} -gt 1000 ]];then
        PIDNUM=$[$PIDNUM-$i]
        break;
    fi
done

ACTIVENUM=`last|head -n -1|cut -d ' ' -f 1|uniq|wc -l` 
ACTIVE=(`last | head -n -1 | cut -d ' ' -f 1 | uniq`)
for ((i=3;i<$ACTIVENUM;i++));do
    if [[ "${ACTIVE[0]}" == "${ACTIVE[2]}" || "${ACTIVE[1]}" == "${ACTIVE[2]}" ]];then
        ACTIVE[2]=${ACTIVE[$i]};
    else
        break;
    fi
done

ROOT=`grep sudo /etc/group | cut -d: -f 4 | tr ',' ' '`
NOWIOGIN=(`w -h | tr -s ' ' '+' | cut -d '+' -f 1`)
NOWIP=(`w -h | tr -s ' ' '+' | cut -d '+' -f 3`)
NOWTTY=(`w -h | tr -s ' ' '+' | cut -d '+' -f 2`)
NOWNUM=`w -h | tr -s ' ' ' ' | cut -d ' ' -f 1 | wc -l`

for ((i=0;i<$NOWNUM;++i));do 
    if [[ $i==0 ]];then
        NOWOUT=${NOWIOGIN[$i]}_${NOWIP[$i]}_${NOWTTY[$i]}
    else
        NOWOUT=$NOWOUT,${NOWIOGIN[$i]}_${NOWIP[$i]}_${NOWTTY[$i]}
    fi

    if [[ $NOWIOGIN == ' ' ]];then
        break;
    fi
done
echo $DATE $PIDNUM [${ACTIVE[0]} ${ACTIVE[1]} ${ACTIVE[2]}] [$ROOT] $NOWOUT
