/*************************************************************************
	> File Name: master.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年05月04日 星期五 00时01分57秒
 ************************************************************************/

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include "socket.h"
int bindSocket;
int sendSocket;
void send_all_req() {
    for (int i = 1; i <= 1; ++i) {
        send(sendSocket, &i,sizeof(int), 0);
        int stat = 0;
        while(recv(sendSocket, &stat, sizeof(int), 0) > 0) {
            int newClient = accept(bindSocket,(struct sockaddr*)NULL,NULL);
            if (stat == 201) {
                char data[1005] = {0};
                while(recv(newClient, data, sizeof(data), 0) > 0){
                    char command[1024] = {0};
                    sprintf(command, "echo \"%s\" >> log/CPU_INFO", data);
                    printf("%s", command);
                    system(command);
                    break;
                }
            }
            break;
        }
    }
}
int main() {
    sendSocket = socket_create();
    bindSocket = socket_create();
    socket_bind(bindSocket, 2022);
    socket_connect(sendSocket, 2011, "192.168.1.44");
    send_all_req();
    return 0;
}
