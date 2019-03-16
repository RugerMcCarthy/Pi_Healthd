#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "socket.h"
int sendSocket;
int bindSocket;
int main() {
    bindSocket = socket_create();
    socket_bind(bindSocket, 2011);
    while (true) {
        struct sockaddr_in  client_addr;
        socklen_t len = sizeof(client_addr);
        int newMaster = accept(bindSocket,(struct sockaddr *)&client_addr, &len);
        if (newMaster < 0) continue;
        char client_ip[32] = {0};
        inet_ntop(AF_INET, (void*)&client_addr.sin_addr,client_ip, 32);
        printf("%s\n", client_ip);
        int pid = fork();
        if (pid > 0) continue;
        int stat = 0;
        while (recv(newMaster, &stat, sizeof(stat), 0) > 0) { 
		int open_file = stat + 200;
		sendSocket = socket_create();
		send(newMaster, &open_file, sizeof(int), 0);
		int yes = 0;
		while (recv(newMaster, &yes, sizeof(int), 0) > 0) {
			if (yes == 1){
				break;
			}
		}
		socket_connect(sendSocket, 2022, client_ip);
            	FILE* command = NULL;
		switch (open_file){
			case 201: {
				command = popen("bash shell/MEM.sh", "r");
			}break;
			case 202: {
				command = popen("bash shell/DISK.sh", "r");
			}break;
			case 203: {
				command = popen("bash shell/CPU.sh", "r");
			}break;
			case 204: {
				command = popen("bash shell/OS_INFO.sh", "r");
			}break;
			case 205: {
				command = popen("bash shell/USER.sh", "r");
			}break;
		}
		char str[1024] = {0};
		char ans[1024] = {0};
		while(fgets(str, sizeof(str), command)) {
			strcat(ans,str);
		}	
		printf("%s\n", ans);
		send(sendSocket, ans, strlen(ans), 0);
        }
    }
    return 0;
}
