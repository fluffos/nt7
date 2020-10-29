// socket_d.c

#include <net/socket.h>
#include <net/socket_errors.h>

#undef DEBUG
#define monitor(x)              CHANNEL_D->channel_broadcast("nch", "SOCKET_D 精灵："+(string)x)
#define PROCESS_TIMEOUT         30

inherit F_DBASE;

int clean_up() { return 1; }

nosave string hostip;
nosave mapping sockets = allocate_mapping(0);
mapping query_sockets() { return sockets; }
void close_callback(int fd);

void delete_sockets()
{
        if( !sizeof(sockets) )
                return;

        foreach( int fd in keys(sockets) )
                socket_close(fd);

        sockets = allocate_mapping(0);
        return;
}

int is_ip(string fmt)
{
        string *each_field = explode(fmt, ".");

        if (sizeof(each_field) < 4)
                return 0;

        foreach (string field in each_field)
                foreach (int char in field)
                        if (char < '0' || char > '9')
                                return 0;
        return 1;
}

void resolve_callback(string addr, string ip, int key)
{
        if( stringp(ip) && (ip != "") )
        {
                hostip = ip;
        }
}

void connect_timeout(int fd)
{
        if (undefinedp(sockets[fd]))
                return;

        if (objectp(sockets[fd]["owner"]))
                evaluate(sockets[fd]["stat_callback"], fd,
                         "Unable to connect to remote host: Connection timeout");

        close_callback(fd);
        return;
}

void read_callback(int fd, mixed msg)
{
        if (undefinedp(sockets[fd]))
                return;

        if (! sockets[fd]["owner"])
                return;

        evaluate(sockets[fd]["rece_callback"], fd, msg);

        return;
}

void write_callback(int fd)
{
        sockets[fd]["write_fd"] = fd;

        if (! undefinedp(sockets[fd]["connect_handle"]))
        {
                remove_call_out(sockets[fd]["connect_handle"]);
                // call_out((: connect_timeout :), PROCESS_TIMEOUT, fd);
                call_out((: close_callback :), PROCESS_TIMEOUT, fd);
                map_delete(sockets[fd], "connect_handle");
        }

        // 如果收到 socket write callback 时
        // buffer 内有讯息未传送则立即传送，并清除 buffer
        if (sockets[fd]["write_buffer"])
        {
                socket_write(fd, sockets[fd]["write_buffer"]);
                sockets[fd]["write_buffer"] = 0;
        }

        return;
}

void close_callback(int fd)
{
#ifdef DEBUG
        monitor("socket_close: " + fd);
#endif

        if (undefinedp(sockets[fd]))
                return;

        if (! objectp(sockets[fd]["owner"]))
        {
                socket_close(fd);
                map_delete(sockets, fd);
                return;
        }

        if (! undefinedp(sockets[fd]["clos_callback"]))
        {
                evaluate(sockets[fd]["clos_callback"], fd);
        } else
                socket_close(fd);

        if (! undefinedp(sockets[fd]["connect_handle"]))
        {
                remove_call_out(sockets[fd]["connect_handle"]);
                map_delete(sockets[fd], "connect_handle");
        }

        map_delete(sockets, fd);
        return;
}

void close_socket(int fd)
{
        if (undefinedp(sockets[fd]))
                return;

        socket_close(fd);
        return;
}

void socket_send(int fd, mixed buf)
{
        int res;

#ifdef DEBUG
        monitor("送出讯息: " + buf);
#endif

        if (! buf || buf == "")
                return;

        // 尚未收到 socket write callback 前，将欲传送的讯息存入 buffer
        if (! sockets[fd]["write_fd"])
        {
                if (! sockets[fd]["write_buffer"])
                        sockets[fd]["write_buffer"] = buf;
                else
                        sockets[fd]["write_buffer"] += buf;
                return;
        }

        // 如果 buffer 中有讯息尚未送出，则与本次讯息同时送出
        if( sockets[fd]["write_buffer"] )
        {
                sockets[fd]["write_buffer"] += buf;
                res = socket_write(fd, sockets[fd]["write_buffer"]);
        } else
                res = socket_write(fd, buf);

        switch (res)
        {
        case EESUCCESS:                         /* 传输成功 */
        case EECALLBACK:                        /* 等待完成 */
                sockets[fd]["write_buffer"] = 0;
                break;

        case EEALREADY:                         /* 程序已进行 */
        case EEWOULDBLOCK:                      /* 程序停滞 */
        case EESEND:                            /* 传送资料错误 */
                if (! sockets[fd]["write_buffer"])
                        sockets[fd]["write_buffer"] = buf;

                call_out((: socket_send :), 1, fd, "");
                break;
        default:                                /* 其他错误 */
                if (objectp(sockets[fd]["owner"]))
                        evaluate(sockets[fd]["stat_callback"], fd, socket_error(res));

                close_callback(fd);
                break;
        }
}

varargs int socket_open(string host, int port, int mode,
        function rece_callback,
        function clos_callback,
        function stat_callback)
{
        int socket_fd, res;
        string addr;

        if ( !sizeof(host) ) return -1;

        hostip = host;

        // if (sscanf(hostip, "%*d.%*d.%*d.%*d") != 4)
        if (! is_ip(hostip))
        {
                resolve(hostip, "resolve_callback");
                monitor(sprintf("解析主机位置: %O", hostip));
        }

#ifdef DEBUG
        monitor("socket_open: " + sprintf("%s %d %O %O %O",
                hostip, port, rece_callback, clos_callback, stat_callback));
#endif

        mode = mode || STREAM_BINARY;

        socket_fd = socket_create(mode, (: read_callback :), (: close_callback :));
        if (socket_fd < 0)
        {
#ifdef DEBUG
                monitor("socket_create: " + socket_error(socket_fd));
#endif
                evaluate(stat_callback, socket_fd, "socket_create: " + socket_error(socket_fd));
                return -1;
        }

        sockets[socket_fd] = allocate_mapping(0);

        addr = sprintf("%s %d", hostip, port);
        res = socket_connect(socket_fd, addr, (: read_callback :), (: write_callback :));

        if (res != EESUCCESS)
        {
#ifdef DEBUG
                monitor("socket_connect: " + socket_error(socket_fd));
#endif
                evaluate(stat_callback, socket_fd, "socket_connect: " + socket_error(res));
                close_callback(socket_fd);
                return -1;
        }

        sockets[socket_fd]["addr"] = hostip;
        sockets[socket_fd]["port"] = port;
        sockets[socket_fd]["owner"] = previous_object();
        sockets[socket_fd]["rece_callback"] = rece_callback;
        sockets[socket_fd]["clos_callback"] = clos_callback;
        sockets[socket_fd]["stat_callback"] = stat_callback;

        sockets[socket_fd]["connect_handle"] = call_out((: connect_timeout :),
                                                        PROCESS_TIMEOUT, socket_fd);

        return socket_fd;
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "SOCKET精灵");
}

void remove(string euid)
{
        if( !this_player() )
                return;

        if( sizeof(sockets) > 0 )
                error("SOCKET精灵：目前正在执行SOCKET任务，你不能摧毁SOCKET精灵。\n");
}
