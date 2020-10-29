// cruise.h

#ifndef _CRUISE_H_
#define _CRUISE_H_

#define CRUISE_USER_DATA        0               // 玩家DBASE数据

// 认证信息
#define USER_ID                 0
#define USER_SITE               1
#define USER_MAGIC_NUMBER       2

// CRUISE-FTP的错误号
#define RESULT_OK               "1 "            // 结果正常
#define RESULT_CRUISE           "2 "            // 返回版本
#define RESULT_FILE             "10 "           // 返回文件
#define RESULT_NO_CRUISE        "90 "           // 没有版本
#define RESULT_FINISH           "91 "           // 同步完毕
#define RESULT_ERR              "99 "           // 未知错误

// CRUISE-FTP服务器端的状态
#define STATUS_LOGIN            1               // 刚刚登录
#define STATUS_WAIT_COMMAND     2               // 等待命令
#define STATUS_SENDING          3               // 发送文件

// CRUISE-FTP客户端的状态
#define STATUS_CONNECTING       101             // 连接中
#define STATUS_GET_ITEM         102             // 获得版本
#define STATUS_GET_ITEM_ID      103             // 获得版本数据
#define STATUS_GET_FILE         104             // 读取文件
#define STATUS_SYN              105             // 漫游中
#define STATUS_FINISHED         106             // 漫游结束

// CRUISE-FTP信息结构中的条目
#define STATUS                  0               // 状态
#define FILE_NAME               1               // 文件名字
#define FILE_POS                2               // 文件位置
#define FILE_SIZE               3               // 文件大小
#define CMD_QUEUE               4               // 待处理的命令
#define PENDING_WRITE           5               // 等待发送的信息
#define CMD_BUFFER              6               // (服务器端)缓冲区
#define RESULT_BUFFER           6               // (客户端)缓冲区
#define SUB_SITES               7               // 站点名字

// 每次通常应答返回的长度
#define NORMAL_RESULT_LEN       80              // 80个字节

// 每次发送的文件块大小
#define FILE_BLOCK              1460            // 每次发送1460

#endif
