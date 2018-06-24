/*************************************************************************
	> File Name: socket.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年05月04日 星期五 00时00分14秒
 ************************************************************************/

int socket_create() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() error\n");
        return -1;
    }
    return sockfd;
}
int socket_bind(int sockfd, int port){
	int yes = 1;
	struct sockaddr_in sock_addr;
	//设置本地套接字地址
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(port); //转化为网络字节序
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY); //0.0.0.0

	//设置本地套接字
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		close(sockfd);
		perror("setsockopt() error\n");
		return -1;
	}

	//绑定本地套接字到套接字
	if (bind(sockfd, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) < 0) {
		close(sockfd);
		perror("bind() error\n");
		return -1;
	}

	//将套接字设置为监听状态
	if (listen(sockfd, 20) < 0) {
		close(sockfd);
		perror("listen() error");
		return -1;
	}
	return sockfd;
}
int socket_connect(int sockfd, int port, char* host) {
    struct sockaddr_in dest_addr;
    dest_addr.sin_family=AF_INET;
    dest_addr.sin_port=htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(host);
    if(connect(sockfd,(struct sockaddr *)&dest_addr, sizeof(dest_addr))<0){
        perror("connect");
        return -1;
    }
    return sockfd;
}
