/*
 * client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"


int main(int argc, char **argv) {
    int clientfd;
    char *num1, *num2;
    char *host, *port;
    rio_t rio;
    char buf[MAXLINE];
    char xml[MAXLINE];

    if (argc != 3) {
        fprintf(stderr, "usage: %s <num1> <num2>\n", argv[0]);
        exit(0);
    }

    num1 = argv[1];
    num2 = argv[2];

    sprintf(xml,"<?xml version=\"%s\"?>\r\n"
    "<methodCall>\r\n"
    "<methodName>sample.addmultiply</methodName>\r\n"
    "<params>\r\n"
    "<param>\r\n"
    "<value><double>%s</double></value>\r\n"
    "</param>\r\n"
    "<param>\r\n"
    "<value><double>%s</double></value>\r\n"
    "</param>\r\n"
    "</params>\r\n"
    "</methodCall>\n\n","1.0",num1, num2);

    sprintf(buf, "POST /RPC2 HTTP/1.1\r\n""Content-Type: text/xml\r\n""Content-Length: %i\r\n\n%s",strlen(xml),xml);

    host = "localhost";
    port = "8080";

    clientfd = Open_clientfd(host, port);
    Rio_writen(clientfd, buf, sizeof(buf));
    Rio_readinitb(&rio, clientfd);

    char num;
    char *ptr;
    char read = Rio_readlineb(&rio, buf, sizeof(buf));
    printf ("%s",read);
    //while (Rio_readlineb(&rio, buf, sizeof(buf)) > 0){
        while (read > 0){
        //printf("%s",buf);
        if((ptr = strstr(buf,"double")) != NULL){
            ptr = ptr + 7;
            num = *ptr;
            while(num != '<'){
                printf("%c",(num));
                ptr++;
                num = *ptr;
            }
            printf("  ");
        }
    }
    /*while (Fgets(buf, MAXLINE, stdin) != NULL) {
    	Rio_readlineb(&rio, buf, MAXLINE);
    	Fputs(buf, stdout);
        //printf(buf);
    }*/


    //Rio_writen(clientfd, buf, strlen(buf));
    //Rio_readlineb(&rio, buf, MAXLINE);
    //Fputs(buf, stdout);
    //printf("%s" , buf);
    Close(clientfd);
    exit(0);
}