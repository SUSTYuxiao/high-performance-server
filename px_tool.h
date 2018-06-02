//
// Created by 张鹏霄 on 2018/5/19.
// tool包含了业务无关的公有函数
//

#ifndef HIGH_PERFORMANCE_SERVER_TOOL_H
#define HIGH_PERFORMANCE_SERVER_TOOL_H

#define MAX_QUEUE 1024 //listen的第二个参数，存储三次握手的已完成队列
#define NO_BLOCK 0x0004;
#define DEAULT_PORT 8888

int get_CPU_core_num();
void printError_exit(char *c);
int px_init_socket(int portNum);
void px_accept(int listenFd, int epollFd, char *path);

#endif //HIGH_PERFORMANCE_SERVER_TOOL_H
