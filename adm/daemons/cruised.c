// Copyright (C) 2005, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.
// cruised.c 漫游精灵

#ifdef LONELY_IMPROVED

#include <ansi.h>
#include <mudlib.h>
#include <net/socket.h>
#include <cruise.h>

// #pragma optimize
// #pragma save_binary

inherit F_DBASE;

#include "/adm/etc/database.h"

// 漫游精灵如何工作？
// 每个站点的漫游精灵负责进行认证和数据传输。启动以后，漫游
// 精灵会监听一个端口，查询来自其他站点的请求。
//
// 数据漫游：
// 如果某个站点登陆了其他站点漫游过来的使用者，则本站点从原
// 始站点漫游精灵那里获得该玩家的数据，包括 login & user 以
// 及 item 三部分，由于 dbased 和 news 里的数据用的是数据库
// 来处理，所以就不需要漫游。然后根据这些数据在本站点构造一
// 个玩家，这些数据会在原始站被删除以确保各站数据唯一性，在
// 退出的时候不会传递回原先的站点，而保留在现在的站点。玩家
// 使用这种方式进行漫游。
//
// 配套支持：
// 数据库 mysql 需记录玩家的 id  所在的站点、密码以及姓名以
// 保证 id 的唯一性。数据库还需处理 dbased 中数据以保证漫游
// 过来的数据能得到有效使用。
//
// 认证流程：
// 漫游精灵接受来自连线精灵的数据验证请求，并将从需要请求得
// 站点或的数据。发送请求是需要包括用户名和站点 -- 这个必须
// 通过一定手段进行保密。接受请求以后将查验是否通过并返回相
// 应的信息。接收到返回的正确信息以后，漫游精灵重新驱动起连
// 线精灵。
//
// 监听的端口(以MUD的启动端口为基准)
#define CRUISE_PORT                     21

// 经过授权的地址
#define AGENT_IP   ({ "127.0.0.1", })

#if 0
#define DEBUG_LOG(s)       tell_object(find_player("lonely"), s)
#else
#define DEBUG_LOG(s)
#endif

// 从版本服务器取回的文件后缀
#define APPENDFIX       ".cru"
#define STATUS_INIT                     0
#define STATUS_CONNECT                  1
#define MAX_AUTHENTICATING_USER         20

nosave int status = STATUS_INIT;
nosave mixed *cruise_queue = allocate(MAX_AUTHENTICATING_USER);
nosave int next_cruise = 0, queue_pointer = 0;

// 保存二进制代码的路径
nosave string bin_path;

nosave int cfd;
nosave string *cruise_file = ({ });
nosave mapping socket_info;

// 客户端的连接信息
nosave mixed *client_info = 0;
// 传送的文件
string *fetch_file_list = 0;

// 提供给外部的接口
int fetch_file(string file, string sites);
int authenticate_user(object ob, string sites);

protected void send_file(int fd, string file, string peer_name);
protected void server_init();
protected void in_listen_callback(int fd);
protected void in_read_callback(int fd, string str);
protected void in_write_callback(int fd);
protected void in_close_callback(int fd);
protected void parse_cmd(int fd);
protected void debug_info(string msg);
protected void cmd_getfile(int fd, string arg);
protected void cmd_get(int fd, string arg);
protected void cmd_close(int fd, string arg);
protected void syn_receive_result(string str);
protected void syn_fetch_file_from_server();
protected void syn_finish();
protected void sys_info(string msg);
protected void send_command(int fd, string cmd);
protected void send_cruise_file(string id, int fd);
protected int  syn_get_id_data();
protected int  send_error_msg(int fd, string msg);
protected int  send_pending_msg(int fd);
protected int  send_result(int fd, string msg);
protected int  connect_server();
protected int  syn_receive_file(buffer buf);
protected int  send_client_pending_msg();
protected void syn_close_callback(int fd);
protected void send_timeout(int fd);
int clear_syn_info();

int clean_up() { return 1; }

void create()
{
        seteuid(ROOT_UID);
        bin_path = get_config(__SAVE_BINARIES_DIR__);
        set("channel_id", "漫游精灵");

        call_out("server_init", 0);
}

protected void remove_from_queue()
{
        mixed *cruise;

        cruise = cruise_queue[queue_pointer];
        if (cruise[USER_ID])
        {
                DATABASE_D->db_set_user(cruise[USER_ID], "online", 0);
                DATABASE_D->db_set_user(cruise[USER_ID], "last_station", LOCAL_STATION);
        }

        cruise_queue[queue_pointer] = 0;
        queue_pointer = (queue_pointer + 1) % MAX_AUTHENTICATING_USER;
}

void heart_beat()
{
        mixed *cruise;

        if (status != STATUS_INIT)
                return;

        if (next_cruise == queue_pointer)
        {
                next_cruise = 0;
                queue_pointer = 0;
                cruise_queue = allocate(MAX_AUTHENTICATING_USER);
                set_heart_beat(0);
                return;
        }

        if (! fetch_file_list)
                fetch_file_list = 0;

        if (! connect_server())
        {
                cruise = cruise_queue[queue_pointer];
                if (cruise[USER_ID])
                {
                        DATABASE_D->db_set_user(cruise[USER_ID], "online", 0);
                        DATABASE_D->db_set_user(cruise[USER_ID], "last_station", LOCAL_STATION);
                }
                log_file("cruise", sprintf("%s Failed to create socket or connect server.\n",
                                   log_time()));
        }
}

mixed query_queue()
{
        return cruise_queue;
}

void restore_cruise()
{
        socket_close(cfd);
        cfd = 0;
        socket_info = ([ ]);
        client_info = ({ });
        next_cruise = 0;
        queue_pointer = 0;
        cruise_queue = allocate(MAX_AUTHENTICATING_USER);
}

void remove(string euid)
{
        if (! this_player())
                return;

        if (sizeof(socket_info) > 0)
                error("漫游精灵：目前正在有站点和本站漫游数据，你不能摧毁漫游精灵。\n");

        if (cfd && arrayp(client_info) && client_info[STATUS] != STATUS_FINISHED)
                error("漫游精灵：目前数据正在漫游中，你不能摧毁漫游精灵。\n");
}

// 提供版本服务
protected void server_init()
{
        int port;

        CHANNEL_D->do_channel(this_object(), "sys", "漫游精灵已经启动。");

        // 创建漫游通讯的SOCKET
        cfd = socket_create(STREAM_BINARY,
                            "in_read_callback",
                            "in_close_callback" );

        if (cfd < 0)
        {
                log_file("cruise", sprintf("%s Failed to create socket.\n", log_time()));
                return;
        }

        // 然后绑定SOCKET
        port = __PORT__ + CRUISE_PORT;
        if (socket_bind(cfd, port) < 0)
        {
                log_file("cruise", sprintf("%s Failed to bind socket.\n", log_time()));
                socket_close(cfd);
                return;
        }

        // 最后监听
        if (socket_listen(cfd, "in_listen_callback" ) < 0)
        {
                log_file("cruise", sprintf("%s Failed to listen to socket.\n", log_time()));
                return;
        }

        // 初始化连接信息
        socket_info = ([ ]);
}

// 本地站监听来自其他站点的请求
protected void in_listen_callback(int fd)
{
        int new_fd;
        string address;
        string ip;
        int port;

        if ((new_fd = socket_accept(fd, "in_read_callback",
                                        "in_write_callback")) < 0)
                // 没有成功的接收这个连接请求
                return;

        address = socket_address(new_fd);
        if (! stringp(address) || sscanf(address, "%s %d", ip, port) != 2 ||
            // ! CONFIG_D->query(ip))
            member_array(ip, AGENT_IP) == -1)
        {
                // 这个地址没有经过授权
                sys_info(sprintf("站点 %s 地址没有经过授权。",
                         stringp(address) ? address : "unknow"));
                socket_close(new_fd);
                return;
        }

        sys_info(sprintf("站点 %s 连接本服务器开始构建通讯。", ip));

        socket_info[new_fd] = allocate(8);
        socket_info[new_fd][STATUS] = STATUS_LOGIN;
        socket_info[new_fd][CMD_BUFFER] = "";
        socket_info[new_fd][CMD_QUEUE] = ({ });
        socket_info[new_fd][PENDING_WRITE] = ({ });
        socket_info[new_fd][SUB_SITES] = "不详";

        // 更新状态
        socket_info[new_fd][STATUS] = STATUS_WAIT_COMMAND;
        in_write_callback(new_fd);

}

// 接受信息
protected void in_read_callback(int fd, mixed mess)
{
        int cc;
        string *cmds;
        mixed  prefix;
        string str;

        if (! arrayp(socket_info[fd]))
                return;

        if (stringp(mess))
                // 接收到了字符串
                str = mess;
        else
        if (bufferp(mess))
                // 接收到了缓冲区
                str = read_buffer(mess, 0, sizeof(mess));
        else
                return;

        if (! str) return;

        str = replace_string( str, "\r", "");
        if (stringp(prefix = socket_info[fd][CMD_BUFFER]))
                str = (string) prefix + str + "\n";
        else
                str += "\n";

        cmds = explode(str, "\n");
        socket_info[fd][CMD_BUFFER] = cmds[sizeof(cmds) - 1];

        if (sizeof(cmds) > 1)
        {
                // 将这些命令放入到命令队列中
                cc = sizeof(socket_info[fd][CMD_QUEUE]);
                socket_info[fd][CMD_QUEUE] += cmds[0..<2];
                if (socket_info[fd][STATUS] == STATUS_WAIT_COMMAND)
                        // 正在接受命令状态
                        parse_cmd(fd);
        }
}

// 成功写入
protected void in_write_callback(int fd)
{
        buffer buf;
        string file;
        int pos, len;
        int i;

        for (i = 0; i < 32; i++)
        {
                // 循环处理消息
                reset_eval_cost();

                // 已经处理完了？
                if (! arrayp(socket_info[fd]))
                        // 是，这个不需要继续处理了
                        return;

                // 如果有阻塞的普通消息，则我发送出去
                while (sizeof(socket_info[fd][PENDING_WRITE]))
                {
                        // 有阻塞的消息，发送之
                        if (send_pending_msg(fd) != 0)
                                // 没有成功的发送，等待下一次发送
                                return;
                }

                // 根据当前的状态进行进一步处理
                switch (socket_info[fd][STATUS])
                {
                case STATUS_SENDING:
                        // 正在发送文件
                        pos = socket_info[fd][FILE_POS];
                        len = socket_info[fd][FILE_SIZE] - pos;
                        if (len > FILE_BLOCK)
                                len = FILE_BLOCK;
                        if (len > 0)
                        {
                                buf = read_buffer((string) socket_info[fd][FILE_NAME], pos, len);
                                if (sizeof(buf) != len)
                                        // 读取没有完全成功？填写零发送。
                                        buf = allocate_buffer(len);
                                // 判断这次操作的结果
                                switch (socket_write(fd, buf))
                                {
                                case EESUCCESS:
                                        // 移动游标
                                        pos += len;
                                        break;

                                case EECALLBACK:
                                        // 移动游标
                                        pos += len;

                                        // 等待CALLBACK，先不继续处理
                                        socket_info[fd][FILE_POS] = pos;
                                        return;

                                case EEWOULDBLOCK:
                                        // 发送忙
                                        call_out("in_write_callback", 2, fd);
                                        return;

                                default:
                                        // 发送失败，等待下次callback
                                        return;
                                }
                        }

                        // 判断文件是否发送完毕
                        if ((socket_info[fd][FILE_POS] = pos) >=
                            socket_info[fd][FILE_SIZE])
                        {
                                file = socket_info[fd][FILE_NAME];
                                // 暂时取消了将被漫游的资料文件更名即取消了删除被漫游的资料文件
                                // rename(file, file + ".oo");

                                // 文件已经发送完毕，更新状态
                                socket_info[fd][STATUS] = STATUS_WAIT_COMMAND;
                                if (! sizeof(socket_info[fd][CMD_QUEUE]))
                                        // 已经没有待处理的命令了
                                        return;

                                // 继续处理命令：为什么要用
                                // this_object() 进行呼叫？
                                // 这个是不能省略的，因为这
                                // 样其它部分的函数就可以根
                                // 据previous_object() 分辨
                                // 是否试运行在callback内。
                                this_object()->parse_cmd(fd);

                                // 继续，循环将会处理命令产生的结果
                        }

                        // 发送处理完毕
                        break;

                default:
                        // 未定义状态，无操作
                        return;
                }

                // 一次处理(switch)完毕，循环继续处理
        }

        // 运行太久了
        debug_info("向 SOCKET 写入数据太多，暂缓。");
        call_out("in_write_callback", 1, fd);
}

// 连接断开
protected void in_close_callback(int fd)
{
        string address;

        address = socket_address(fd);
        if (stringp(address))
                sscanf(address, "%s %*d", address);
        else
                address = "unknow";

        sys_info(sprintf("站点 %s 和本站断开了连接。", address));

        // 清除信息
        map_delete(socket_info, fd);
}

// 供 LOGIN_D 调用的接口
int authenticate_user(object ob, string sites)
{
        int is_cruise;
        int next_next;
        string cruise_id;

        if( !stringp(cruise_id=query("id", ob)) )
                return 0;

        if (! stringp(sites) || sites == LOCAL_STATION)
        {
                write(HIY "该人物所在的站点没有得到确认或正在本站，漫游被强行中止。\n" NOR);
                return 0;
        }

        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();

        is_cruise = DATABASE_D->db_query_user(cruise_id, "online");

        if (is_cruise == 3)
        {
                write(HIY "由于同时在漫游该人物档案，漫游被强行中止。\n" NOR);
                return 0;
        }

        next_next = (next_cruise + 1) % MAX_AUTHENTICATING_USER;
        if (next_next == queue_pointer)
        {
                // 同时允许漫游的玩家数量超过上限
                write(HIY "漫游队列已满，请稍后在再进行数据漫游。\n" NOR);
                return 0;
        }

        cruise_queue[next_cruise] = allocate(2);
        cruise_queue[next_cruise][USER_ID] = cruise_id;
        cruise_queue[next_cruise][USER_SITE] = sites;
        next_cruise = next_next;

        DATABASE_D->db_set_user(cruise_id, "online", 3);

        write(HIR "连接站点服务器获取人物的数据中..，请稍后再尝试登陆。\n" NOR);

        set_heart_beat(1);
        return 1;
}

// 向站点服务器端发送命令
void send_command(int fd, string cmd)
{
        if (! fd)
                // 检查当前连接的CFD
                if (! (fd = cfd)) return;


        cmd += "\n";
        if (sizeof(client_info[PENDING_WRITE]))
        {
                // 已经有阻塞需要发送的数据了，这次发送的数
                // 据先阻塞
                client_info[PENDING_WRITE] += ({ cmd });
                return;
        }

        switch (socket_write(fd, cmd))
        {
        case EESUCCESS:
        case EECALLBACK:
                // 发送成功了
                return;

        case EEWOULDBLOCK:
                // 发送数据阻塞
                client_info[PENDING_WRITE] += ({ cmd });
                call_out("syn_write_callback", 2, fd);
                return;

        default:
                // 发送失败
                client_info[PENDING_WRITE] += ({ cmd });
                return;
        }
}

// 发送阻塞的消息

protected int send_pending_msg(int fd)
{
        string result;

        result = socket_info[fd][PENDING_WRITE][0];

        switch (socket_write(fd, result))
        {
        case EESUCCESS:
                // 发送成功了
                socket_info[fd][PENDING_WRITE] = socket_info[fd][PENDING_WRITE][1..<1];
                return 0;

        case EECALLBACK:
                // 需要等待
                socket_info[fd][PENDING_WRITE] = socket_info[fd][PENDING_WRITE][1..<1];
                return -1;

        case EEWOULDBLOCK:
                // 发送数据阻塞
                call_out("in_write_callback", 2, fd);
                return -1;

        default:
        }
}

// 由于命令简单，不采用常规的语法分析。
protected void parse_cmd(int fd)
{
        string cmd;
        string word, arg;

        // 取出一条命令进行处理
        cmd = socket_info[fd][CMD_QUEUE][0];
        socket_info[fd][CMD_QUEUE] = socket_info[fd][CMD_QUEUE][1..<1];

        if (sscanf(cmd, "%s %s", word, arg) != 2)
        {
                word = cmd;
                arg = 0;
        }

        switch (word)
        {
        case "getfile":
                cmd_getfile(fd, arg);
                break;

        case "get":
                cmd_get(fd, arg);
                break;

        case "close":
                cmd_close(fd, arg);
                break;
        }
}

// 读取玩家自造数据
protected void cmd_getfile(int fd, string arg)
{
        string id;
        string mudn;

        if (stringp(arg) && sscanf(arg, "%s from %s", id, mudn) == 2)
        {
                sys_info(sprintf("站点 %s正在读取验证信息，准备漫游玩家(%s)数据。", mudn, id));
                socket_info[fd][SUB_SITES] = mudn;
        }

        send_cruise_file(id, fd);
        return;
}

// 读取某一个文件
protected void cmd_get(int fd, string arg)
{
        string ban;
        int last;

        // 查看文件
        if (! arg || arg[0] != '/')
        {
                send_error_msg(fd, sprintf("no such file(%O).\n", arg));
                return;
        }

        last = strlen(arg) - 2;

        // 发送版本记录下的文件
        send_file(fd, arg, arg);
}

// 关闭连接
protected void cmd_close(int fd, string arg)
{
        string address;

        address = socket_address(fd);
        if (stringp(address))
                sscanf(address, "%s %*d", address);
        else
                address = "unknow";

        sys_info(sprintf("站点 %s 和本站数据漫游完毕。", address));

        send_result(fd, RESULT_FINISH "ok\n");
}

// 向对方发送一条结果信息
protected int send_result(int fd, string msg)
{
        string result;

        result = sprintf("%-" + (NORMAL_RESULT_LEN - 1) + "s.", msg);

        if (sizeof(socket_info[fd][PENDING_WRITE]))
        {
                // 已经有阻塞需要发送的数据了，这次发送的数
                // 据先阻塞
                socket_info[fd][PENDING_WRITE] += ({ result });
                return -1;
        }

        switch (socket_write(fd, result))
        {
        case EESUCCESS:
                // 发送成功了
                return 0;

        case EECALLBACK:
                // 需要等待
                // socket_info[fd][PENDING_WRITE] += ({ result });
                return -1;

        case EEWOULDBLOCK:
                // 发送数据阻塞
                socket_info[fd][PENDING_WRITE] += ({ result });
                call_out("in_write_callback", 2, fd);
                return -1;

        default:
                socket_close(fd);
        }
}

// 向对方发送一条错误信息
protected int send_error_msg(int fd, string msg)
{
        return send_result(fd, RESULT_ERR + msg);
}

// 向对方发送一个文件
protected void send_file(int fd, string file, string peer_name)
{
        int fs;

        // 直接发送
        if ((fs = file_size(file)) < 0)
        {
                send_error_msg(fd, sprintf("read file(%s) error.\n", file));
                return;
        }

        // 更新状态，然后首先发送文件的长度
        socket_info[fd][FILE_NAME] = file;
        socket_info[fd][FILE_SIZE] = fs;
        socket_info[fd][FILE_POS] = 0;
        socket_info[fd][STATUS] = STATUS_SENDING;
        if (send_result(fd, sprintf(RESULT_FILE "%s %d\n", peer_name, fs)) == 0 &&
            previous_object() != this_object())
                // 成功发送了的应答，并且当前不是由in_write_callback
                // 调用进入，则继续发送文件
                in_write_callback(fd);
}

// 接收文件内容
protected int syn_receive_file(buffer buf)
{
        mixed *st;
        string file;
        int len;
        int sl;

        file = client_info[FILE_NAME];
        len =  client_info[FILE_SIZE] - client_info[FILE_POS];
        if (len > sizeof(buf))
                // 不需要将buf中的数据全部写入
                len = sizeof(buf);

        write_buffer(file + APPENDFIX,
                     client_info[FILE_POS], buf[0..len - 1]);
        client_info[FILE_POS] += len;
        if (client_info[FILE_POS] < client_info[FILE_SIZE])
                // 文件还没有接收完毕
                return len;

        // 成功获取文件完毕
        log_file("cruise", sprintf("%s got file %s.\n",
                                    log_time(), client_info[FILE_NAME]));
        client_info[FILE_POS] = 0;
        client_info[FILE_NAME] = 0;
        client_info[FILE_SIZE] = 0;

        // 查看当前的状态
        switch (client_info[STATUS])
        {
        case STATUS_SYN:
                // 将文件名字修改为正常的名字
                rm(file);
                rename(file + APPENDFIX, file);

                // 如果这个文件是一个C文件，那么我必须删除
                // 它的BIN 文件，因为我需要重新编译它。
                sl = strlen(file) - 2;
                if (sl > 0 && file[sl] == '.' && file[sl + 1] == 'c')
                        rm(bin_path + file[0..sl] + "b");
                break;

        default:
                // 错误的状态
        }

        // 返回使用的BUFFER的长度
        return len;
}

protected int connect_server()
{
        string sites;
        string addr;
        int port;
        int ret_val;
        mixed *cruise;

        cruise = cruise_queue[queue_pointer];

        CHANNEL_D->do_channel(this_object(), "sys", "漫游系统尝试向<" +
                              cruise[USER_SITE] + ">获取人物资料。");

        // 创建版本通讯的SOCKET
        cfd = socket_create(STREAM_BINARY,
                            "syn_read_callback",
                            "syn_close_callback" );

        if (cfd < 0)
        {
                if (cruise[USER_ID])
                {
                        DATABASE_D->db_set_user(cruise[USER_ID], "online", 0);
                        DATABASE_D->db_set_user(cruise[USER_ID], "last_station", LOCAL_STATION);
                }

                log_file("cruise", sprintf("%s Failed to create socket.\n",
                                            log_time()));
                return 0;
        }
        // 目的为关闭该 cfd，系统监听的cfd在这里被改变了，所以监听的cfd不会被关闭
        status = STATUS_CONNECT;
        remove_call_out("send_timeout");
        call_out("send_timeout", 180, cfd);

        // 初始化客户端信息
        client_info = allocate(8);
        client_info[STATUS] = STATUS_CONNECTING;
        client_info[FILE_NAME] = 0;
        client_info[FILE_POS] = 0;
        client_info[FILE_SIZE] = 0;
        client_info[RESULT_BUFFER] = "";
        client_info[PENDING_WRITE] = ({ });

        sites = cruise[USER_SITE];
        port = __PORT__ + CRUISE_PORT;
        // 生成版本服务器的连接地址
        addr = sprintf("%s %d", sites, port);

        ret_val = socket_connect(cfd, addr,
                                 "syn_read_callback",
                                 "syn_write_callback");
        if (ret_val != EESUCCESS)
        {
                status = STATUS_INIT;

                if (cruise[USER_ID])
                {
                        DATABASE_D->db_set_user(cruise[USER_ID], "online", 0);
                        DATABASE_D->db_set_user(cruise[USER_ID], "last_station", LOCAL_STATION);
                }

                log_file("cruise", sprintf("%s Failed to connect server.\n",
                                            log_time()));
                return 0;
        }

        log_file("cruise", sprintf("%s connecting to server %s.\n",
                                    log_time(), addr));
        return 1;
}

// 处理本地接收到的来自其他站点的数据
protected void syn_read_callback(int fd, buffer buf)
{
        string str;
        int len;
        int ver;
        string msg;

        if (fd != cfd || ! bufferp(buf)) return;

        DEBUG_LOG(sprintf(HIC "incoming: buf = %O(%d)\n" NOR, buf, sizeof(buf)));

        do
        {
                if (! client_info[FILE_NAME])
                {
                        // 没有文件名字，接收的是普通应答信息

                        // 计算我应该从缓冲区中读出的字节数目，因为
                        // 可能不能一次获得普通的应答信息，因此我将
                        // 这些信息累计到RESULT_BUFFER中， 一直到读
                        // 满期望的字节为止。那么我这次从缓冲区读出
                        // 来的应该是多少个字节，就应该计算。其中保
                        // 存在FILE_POS中的是我已经读出的字符。
                        len = NORMAL_RESULT_LEN - client_info[FILE_POS];
                        if (len > sizeof(buf))
                                // 这次没有这么多字节可以让我读
                                len = sizeof(buf);
                        client_info[FILE_POS] += len;
                        client_info[RESULT_BUFFER] += read_buffer(buf, 0, len);
                        // 取剩余的buffer
                        buf = buf[len..<1];

                        if (client_info[FILE_POS] >= NORMAL_RESULT_LEN)
                        {
                                // 读到了一条通常的返回信息，重新设
                                // 置缓冲区。
                                str = client_info[RESULT_BUFFER];
                                client_info[RESULT_BUFFER] = "";
                                client_info[FILE_POS] = 0;

                                // 处理接收到的结果信息
                                syn_receive_result(str);
                        }
                }

                DEBUG_LOG(sprintf("buf = %O(%d) ... file_name = %O(%d)\n",
                                                          buf, sizeof(buf),
                                                          client_info[FILE_NAME],
                                                          client_info[FILE_POS]));
                if (bufferp(buf) && client_info[FILE_NAME])
                        // 接收文件
                        buf = buf[syn_receive_file(buf)..<1];

                // 如果buf不为空，则继续处理
        } while (sizeof(buf) && client_info[STATUS] != STATUS_FINISHED);
}

// 漫游时客户端连接的写回调函数
void syn_write_callback(int fd)
{
        if (fd != cfd)
        {
                log_file("cruise", sprintf("socket error: fd = %d vfd = %d\n", fd, cfd));
                return;
        }

        while (sizeof(client_info[PENDING_WRITE]))
        {
                // 有阻塞的消息，发送之
                if (send_client_pending_msg() != 0)
                        // 没有成功的发送，等待下一次发送
                        return;
        }

        // 根据当前的状态处理
        switch (client_info[STATUS])
        {
        case STATUS_CONNECTING:
                if (fetch_file_list)
                {
                        // 指定获得某些文件
                        syn_fetch_file_from_server();
                        break;
                }
                // 刚刚连接，发送取玩家自造数据的命令
                send_command(fd, sprintf("getfile %s from %s(%s)", cruise_queue[queue_pointer][USER_ID],
                                         LOCAL_MUD_NAME(), INTERMUD_MUD_NAME,
                                         __PORT__));
                client_info[STATUS] = STATUS_GET_ITEM;
                sys_info("版本精灵成功的和服务器建立了通讯。");
                break;
        default:
                return;
        }
}
// 系统信息
protected void sys_info(string msg)
{
        CHANNEL_D->do_channel(this_object(), "sys", msg);
}

// 调试信息
protected void debug_info(string msg)
{
        CHANNEL_D->do_channel(this_object(), "debug", msg);
}

// 客户端发送阻塞的消息

protected int send_client_pending_msg()
{
        string msg;

        msg = client_info[PENDING_WRITE][0];
        switch (socket_write(cfd, msg))
        {
        case EESUCCESS:
                // 发送成功了
                client_info[PENDING_WRITE] = client_info[PENDING_WRITE][1..<1];
                return 0;

        case EECALLBACK:
                // 需要等待
                client_info[PENDING_WRITE] = client_info[PENDING_WRITE][1..<1];
                return -1;

        case EEWOULDBLOCK:
                // 发送数据阻塞
                call_out("syn_write_callback", 2, cfd);
                return -1;

        default:
                // 发送失败
                return -1;
        }
}

// 同步时客户端连接的读回调函数
// 由于服务器可能会返回两种数据：1 普通应答信息  2 二进制文
// 件数据。因此接收函数依据状态中的文件名字存在与否来鉴别这
// 两种状态：如果有文件名字，那么就认为是接收文件中，如果没
// 有，则是接收普通应答信息。普通应答信息一定是固定个字节，
// 以ASCII 方式存放。如果一次接收没有满足期望的字节，那么长
// 度将保存在FILE_POS里面。

protected void syn_receive_result(string str)
{
        string file;
        string msg;
        string ver;
        int len;

        if ((len = strsrch(str, '\n')) == -1)
        {
                // 返回的信息不正确 - 必须包含'\n'
                log_file("cruise", sprintf("%s respond without '\\n' from server: %s.\n",
                                            log_time(), str));
                DEBUG_LOG(sprintf(HIR "error syntax str = %s\n" NOR, str));
                return;
        }
        if (! len) return;
        str = str[0..len - 1];

        DEBUG_LOG(sprintf("str = %s\n", str));

        if (sscanf(str, RESULT_ERR "%s", msg))
        {
                // 遇到了错误，先记录进入日志
                log_file("cruise", sprintf("%s error respond: %s\n",
                                            log_time(), msg));
                DEBUG_LOG(str + "\n");
        }

        // 根据当前的状态进行处理
        switch (client_info[STATUS])
        {
        case STATUS_GET_ITEM:
                if (sscanf(str, RESULT_CRUISE "%s", ver))
                {
                        // cruise_file = explode(ver, "|");
                        if (ver != "SEND_CRUISE_FILE_OK")
                                cruise_file += ({ ver });
                        else
                                syn_get_id_data();
                }

                // syn_get_id_data();
                // 没有返回正常的玩家数据信息
                // log_file("cruise", sprintf("%s can not get cruise. server report: %s\n",
                //                            log_time(), str));

                // 怎么办？只有结束漫游
                // syn_finish();
                break;

        case STATUS_SYN:
                // 接收文件的长度
                if (! sscanf(str, RESULT_FILE "%s %d", file, len))
                {
                        if (sscanf(str, RESULT_FINISH "%*s"))
                        {
                                log_file("cruise", sprintf("%s cruise synchronized.\n",
                                                            log_time()));
                                syn_finish();
                        }

                        break;
                }

                DEBUG_LOG(sprintf("file: %s len = %d\n", file, len));

                // 记录的接收文件状态和信息

                // 记录传送来的文件的信息
                client_info[FILE_NAME] = file;
                client_info[FILE_POS] = 0;
                client_info[FILE_SIZE] = len;

                // 如果有，删除这个文件的临时文件
                rm(file + APPENDFIX);

                sys_info(sprintf("getting(%s)...", file));
                break;

        default:
                // 不应该接收到信息
        }
}

// 漫游数据结束
// 结束时可能成功的漫游了，也可能没有。
protected void syn_finish()
{
        mixed *cruise;

        seteuid(ROOT_UID);
        sys_info("漫游精灵：漫游玩家数据结束。");

        cruise = cruise_queue[queue_pointer];

        if (cruise[USER_ID])
        {
                if (! DATABASE_D->query_db_status())
                        DATABASE_D->connect_to_database();

                DATABASE_D->db_set_user(cruise[USER_ID], "online", 0);
                DATABASE_D->db_set_user(cruise[USER_ID], "last_station", LOCAL_STATION);
        }

        if (cfd) { socket_close(cfd); cfd = 0; }

        cruise_file = ({ });

        client_info[STATUS] = STATUS_FINISHED;
        client_info[FILE_NAME] = 0;
        client_info[FILE_POS] = 0;
        client_info[FILE_SIZE] = 0;
        client_info[PENDING_WRITE] = ({ });
        client_info[RESULT_BUFFER] = "";
        remove_from_queue();
        status = STATUS_INIT;  // by Lonely
        fetch_file_list = 0;
}

// 从服务器上获取一批文件
protected void syn_fetch_file_from_server()
{
        int i;

        client_info[STATUS] = STATUS_SYN;

        for (i = 0; i < sizeof(fetch_file_list); i++)
        {
                if (fetch_file_list[i][0] != '/')
                        fetch_file_list[i] = "/" + fetch_file_list[i];
                send_command(cfd, "get " + fetch_file_list[i]);
        }

        send_command(cfd, "close");
}

protected void send_cruise_file(string cruise_id, int fd)
{
        object ob;
        mapping summon, whistle;
        string *ks;
        string *fs;
        string msg;
        string file;
        int i;

        msg = "";
        fs = ({ });

        ob = UPDATE_D->global_find_player(cruise_id);
        summon=query("can_summon", ob);
        whistle=query("can_whistle", ob);
        UPDATE_D->global_destruct_player(ob);

        if (objectp(ob = find_player(cruise_id)))
        {
                tell_object(HIY "由于你的人物数据正在漫游，系统强行使你离线。\n" NOR);
                ob->save();
                destruct(ob);
        }

        if (mapp(summon))
        {
                ks = keys(summon);
                for (i = 0; i < sizeof(ks); i++)
                {
                        file = summon[ks[i]] + ".c";
                        if (file_size(file) > 0)
                        {
                                if (ob = find_object(file))
                                        destruct(ob);

                                send_result(fd, sprintf(RESULT_CRUISE "%s\n", file));
                                // fs += ({ file });
                        }
                }
        }
        if (mapp(whistle))
        {
                ks = keys(whistle);
                for (i = 0; i < sizeof(ks); i++)
                {
                        file = whistle[ks[i]] + ".c";
                        if (file_size(file) > 0)
                        {
                                if (ob = find_object(file))
                                        destruct(ob);

                                send_result(fd, sprintf(RESULT_CRUISE "%s\n", file));
                                // fs += ({ file });
                        }
                }
        }

        file = sprintf(DATA_DIR "beast/%s", cruise_id + "-beast" + __SAVE_EXTENSION__);
        if (file_size(file) > 0)
                send_result(fd, sprintf(RESULT_CRUISE "%s\n", file));
                // fs += ({ file });
        /*
        if (sizeof(fs) >= 2)
                msg += implode(fs[0..sizeof(fs) - 1], "|");
        else
        if (sizeof(fs) == 1)
                msg += fs[0];

        if (! msg)
                send_result(fd, RESULT_NO_CRUISE "no file need to cruise\n");
        else
                send_result(fd, sprintf(RESULT_CRUISE "%s\n", msg));
        */

        send_result(fd, sprintf(RESULT_CRUISE "%s\n", "SEND_CRUISE_FILE_OK"));
        return;
}

int syn_get_id_data()
{
        string file;
        int i;
        mixed *cruise;

        cruise = cruise_queue[queue_pointer];

        if (TX_SAVE && CRUISE_USER_DATA)
        {
                file = sprintf(DATA_DIR "login/%c/%s", cruise[USER_ID][0], cruise[USER_ID] + __SAVE_EXTENSION__);
                assure_file(file);
                fetch_file_list = ({ file });
                file = sprintf(DATA_DIR "user/%c/%s", cruise[USER_ID][0], cruise[USER_ID] + __SAVE_EXTENSION__);
                assure_file(file);
                fetch_file_list += ({ file });
        } else
                fetch_file_list = ({ });

        if (arrayp(cruise_file) && sizeof(cruise_file) > 0)
        {
                for (i = 0; i < sizeof(cruise_file); i++)
                {
                        file = cruise_file[i];
                        if (file[0] != '/')
                                file = "/" + file;
                        assure_file(file);
                        fetch_file_list += ({ file });
                }
        }

        sys_info(sprintf("连接站点 %s 成功，开始漫游人物 %s 的数据。", cruise[USER_SITE], cruise[USER_ID]));
        syn_fetch_file_from_server();
        return 1;
}

int fetch_file(string file, string sites)
{
        int next_next;

        next_next = (next_cruise + 1) % MAX_AUTHENTICATING_USER;
        if (next_next == queue_pointer)
        {
                // 同时允许漫游的玩家数量超过上限
                write(HIY "漫游队列已满，请稍后在再进行数据漫游。\n" NOR);
                return 0;
        }

        fetch_file_list = ({ file });

        cruise_queue[next_cruise] = allocate(2);
        cruise_queue[next_cruise][USER_ID] = 0;
        cruise_queue[next_cruise][USER_SITE] = sites;
        next_cruise = next_next;

        write("正在连接服务器获取文件。\n");
        set_heart_beat(1);
        return 1;
}


protected void send_timeout(int fd)
{
        socket_close(fd);
        syn_close_callback(fd);
}

// 漫游时客户端连接断开的回调函数
protected void syn_close_callback(int fd)
{
        remove_call_out("send_timeout");
        // 防止还在漫游中被关闭
        if (queue_pointer == next_cruise &&
            status != STATUS_INIT)
                return;

        if (fd != cfd) return;

        cfd = 0;
        remove_from_queue();
        status = STATUS_INIT;
}

int clear_syn_info()
{
        int result;
        int fd;

        if (previous_object() && ! is_root(previous_object()))
                return 0;

        // 服务器端：清除套接字的连接信息

        if (sizeof(socket_info) > 0)
        {
                foreach (fd in keys(socket_info))
                        if (intp(fd)) socket_close(fd);

                socket_info = ([ ]);
                return 1;
        }

        return 0;


        // 客户端：清除漫游的SOCKET和信息
        if (cfd)
        {
                log_file("cruise", sprintf("%s 暂停了漫游数据的操作。\n", log_time()));
                syn_finish();
                return 1;
        }

        return 0;
}

mixed query_socket_info()
{
        if (previous_object() && ! is_root(previous_object()))
                return 0;

        return socket_info;
}

mixed query_client_info() { return client_info; }
int query_cfd() { return cfd; }

#endif
