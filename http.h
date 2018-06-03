//
// Created by 张鹏霄 on 2018/6/3.
//

#ifndef HIGH_PERFORMANCE_SERVER_HTTP_H
#define HIGH_PERFORMANCE_SERVER_HTTP_H

void do_request(void* ptr);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define BUF_MAX (8*1024)

#endif //HIGH_PERFORMANCE_SERVER_HTTP_H
