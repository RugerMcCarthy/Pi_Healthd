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
    for (int i = 1; i <= 6; ++i) {
        send(sendSocket, &i,sizeof(int), 0);
	int open_file = 0;
        while(recv(sendSocket, &open_file, sizeof(int), 0) > 0) {
		int yes = 1;
		send(sendSocket, &yes, sizeof(int), 0);
		int newClient = accept(bindSocket,(struct sockaddr*)NULL, NULL);
		char data[1005] = {0};
       		while(recv(newClient, data, sizeof(data), 0) > 0){
                	char command[1024] = {0};
			switch(open_file) {
				case 201 :{
					sprintf(command, "echo \"%s\" >> log/MEM_INFO", data);
				}break;
				case 202 :{
					sprintf(command, "echo \"%s\" >> log/DISK_INFO", data);
				}break;
				case 203 :{
					sprintf(command, "echo \"%s\" >> log/CPU_INFO", data);
				}break;
				case 204 :{
					sprintf(command, "echo \"%s\" >> log/OS_INFO", data);
				}break;
				case 205 :{
					sprintf(command, "echo \"%s\" >> log/USER_INFO", data);
				}break;
			}
                        system(command);
                        break;
            	}
		close(newClient);
                break;
        }
    }
    printf("<<< ALL WORKS SECCESS ! PLEASE CHECK LOG CATELOG >>>\n");
}
int main() {
    sendSocket = socket_create();
    bindSocket = socket_create();
    socket_bind(bindSocket, 2022);
    socket_connect(sendSocket, 2011, "192.168.1.44");
    send_all_req();
    return 0;
}
