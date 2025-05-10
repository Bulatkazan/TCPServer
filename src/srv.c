/* srv.c */

#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8183

int main(){

    char buf[512] = {};
    char *data;

    socklen_t addrlen = 0;
    struct sockaddr_in srv, cli;

    memset(&srv, 0, sizeof(srv));
    memset(&cli, 0, sizeof(cli));
    
    int flag = 0;
    int server = socket(AF_INET, SOCK_STREAM, 0);

    if (server < 0) {
        printf("socket() faild\n");
        close(server);
        flag = -1;
    } else {

        srv.sin_family = AF_INET;
        srv.sin_addr.s_addr = 0;
        srv.sin_port = htons(PORT);

        int bind_result = bind(server, (struct sockaddr*)&srv, sizeof(srv));
        if (bind_result){
            printf("bind faild\n");
            close(server);
            flag = -1;
        } else {

            int listen_result = listen(server, 5);
            if (listen_result) {
                printf("listen faild\n");
                close(server);
                flag = -1;
            } else {

                printf("Listening on 0.0.0.0:%d\n", PORT);
                int client = accept(server, (struct sockaddr* )&srv,&addrlen);
                if (client < 0) {
                    printf("accept() faild \n ");
                    close(server);
                    flag = -1;
                } 
                else{

                        printf("Client connected\n");
                        read(client, buf, 511);
                        data = "httpd v1.0\n";
                        write(client, data, strlen(data));
                        close(client);
                        close(server);
                }
            }
        }

    }
    return flag;
}
