// mail daemon
// From JackyBoy

// #pragma optimize
// #pragma save_binary

#include <ansi.h>
#include <net/dns.h>
#include <net/telnet.h>
#include <net/socket.h>
#include <net/socket_errors.h>
#include <socket_err.h>
#include <mudlib.h>

inherit F_DBASE;

#define STATUS_INIT             0
#define STATUS_CONNECT_OK       1
#define STATUS_HELO_OK          2
#define STATUS_START_AUTH       3
#define STATUS_USERNAME_SENT    4
#define STATUS_PASSWORD_SENT    5
#define STATUS_MAIL_FROM_OK     6
#define STATUS_RCPT_TO_OK       7
#define STATUS_DATA_OK          8
#define STATUS_DATA_SENT        9
#define STATUS_QUIT_OK          10
#define        STATUS_FINISH                11

#define MAX_MAIL_IN_QUEUE       20
#define MAX_RETRY_COUNT         3

#define MAIL_FROM               0
#define MAIL_RECEIVER           1
#define MAIL_TOPIC              2
#define MAIL_DATA               3
#define MAIL_ERROR              4

nosave int status = STATUS_INIT;
nosave mixed *mail_queue = allocate(MAX_MAIL_IN_QUEUE);
nosave int next_mail = 0, queue_pointer = 0;
nosave int can_write = 0;
nosave string delay_message;

private int write_message(int fd, string arg);
private int send_mail();
private void remove_from_queue();
private void write_callback(int fd);
private void read_callback(int fd, mixed message);
private void in_close_callback(int fd);

void debug_info(string arg)
{
        if (find_player("lonely"))
                tell_object(find_player("lonely"), arg);
        return;
}

void create()
{
        seteuid(getuid());
        set("channel_id", "邮件精灵");
        write("邮件系统已经启动。\n");
}

int clean_up()
{
        if (! query_heart_beat())
        {
                destruct(this_object());
                return 0;
        }

        return 1;
}

int queue_mail(object me, string mail_from, string mail_to, string topic, string data)
{
        int next_next;

        if (strlen(data) > 65536)
                return notify_fail("你不能发送大于64K的邮件。\n");

        log_file("mail", sprintf("%s %s try to send mail <%s> Size:%d\n",
                                 log_time(),(me?query("id", me):"SYSTEM"),
                                 topic, strlen(data)));

        // allocate a new mail buffer
        next_next = (next_mail + 1) % MAX_MAIL_IN_QUEUE;
        if (next_next == queue_pointer)
                return notify_fail("邮件队列已满，现在无法发送邮件。\n");

        // queue this mail
        if (! mail_from || sscanf(mail_from, "%*s@%*s") != 2)
                mail_from = "lonely-21@163.com";

        if (! mail_to || sscanf(mail_to, "%*s@%*s") != 2)
                return notify_fail("无法向这个地址发送邮件。\n");

        mail_queue[next_mail] = allocate(5);
        mail_queue[next_mail][MAIL_FROM] = mail_from;
        mail_queue[next_mail][MAIL_RECEIVER] = mail_to;
        mail_queue[next_mail][MAIL_TOPIC] = topic;
        mail_queue[next_mail][MAIL_DATA] = data;
        mail_queue[next_mail][MAIL_ERROR] = 0;
        next_mail = next_next;

        set_heart_beat(1);
        return 1;
}

private void remove_from_queue()
{
        mail_queue[queue_pointer] = 0;
        queue_pointer = (queue_pointer + 1) % MAX_MAIL_IN_QUEUE;
}

void heart_beat()
{
        if (status != STATUS_INIT)
                return;

        if (next_mail == queue_pointer)
        {
                // No mail in queue
                next_mail = 0;
                queue_pointer = 0;
                mail_queue = allocate(MAX_MAIL_IN_QUEUE);
                set_heart_beat(0);
                return;
        }

        send_mail();
}

mixed query_queue()
{
        return mail_queue;
}

private string base64 =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                         "abcdefghijklmnopqrstuvwxyz"
                         "01234567890+/";

private int trans_int_to_64(int ch)
{
    return base64[ch];
}

private int trans_64_to_int(int b64)
{
    if (b64 >= 'A' && b64 <= 'Z') return b64 - 'A';
    if (b64 >= 'a' && b64 <= 'z') return b64 - 'a' + 26;
    if (b64 >= '0' && b64 <= '9') return b64 - '0' + 52;
    if (b64 == '+') return 62;
    if (b64 == '/') return 63;
    return 0;
}

// BASE64编码
string encode64(mixed src)
{
        int temp;
        int len;
        buffer buf, dst;
        string ret;
        int i, k;

        if (! stringp(src) && ! bufferp(src))
                error("encode64: expect buffer or string.\n");

        // 编码长度一定是3的倍数
        len = sizeof(src);
        while (len % 0x3) len++;
        buf = allocate_buffer(len);
        dst = allocate_buffer(len / 3 * 4);
        write_buffer(buf, 0, src);

        // 开始编码
        ret = "";
        i = 0;
        k = 0;
        while (i < len)
        {
                temp = buf[i++];
                temp = (temp << 8) + buf[i++];
                temp = (temp << 8) + buf[i++];
                dst[k++] = trans_int_to_64((temp >> 18) & 0x3F);
                dst[k++] = trans_int_to_64((temp >> 12) & 0x3F);
                dst[k++] = trans_int_to_64((temp >>  6) & 0x3F);
                dst[k++] = trans_int_to_64(temp & 0x3F);
        }
        ret = read_buffer(dst, 0, k);
        return ret;
}

private int send_mail()
{
        int err;
        int socket;
        mixed *mail;

        mail = mail_queue[queue_pointer];

        CHANNEL_D->do_channel(this_object(), "sys", "邮件系统尝试向<" +
                              mail[MAIL_RECEIVER] + ">发送邮件。");
        socket = socket_create(STREAM, "in_read_callback", "in_close_callback");
        if (socket < 0)
        {
                log_file("mail", sprintf("%s Failed to create socket for mail to: %s.\n",
                                         log_time(), mail[MAIL_RECEIVER]));
                return 0;
        }

        status = STATUS_CONNECT_OK;
        remove_call_out("send_timeout");
        call_out("send_timeout", 120, socket);
        can_write = 0;
        delay_message = 0;

        err = socket_connect(socket, "127.0.0.1 25", "read_callback", "write_callback");
        if (err != EESUCCESS)
        {
                status = STATUS_INIT;
                log_file("mail", sprintf("%s can not connect smtp server for mail to: %s.\n",
                                         log_time(), mail[MAIL_RECEIVER]));
                return 0;
        }

        return 1;
}

private void read_callback(int fd, mixed message)
{
        mixed *mail;
        string sender;

        mail = mail_queue[queue_pointer];

        // SMTP客户端自动机
        switch (status)
        {
        default:
                return;

            case STATUS_CONNECT_OK:
                // 连接成功
                    if (sscanf(message, "220%*s"))
                    {
                        // 发送HELO命令
                            status = STATUS_HELO_OK;
                            write_message(fd, "HELO " + "smtp");
                            return;
                    }
                    break;

            case STATUS_HELO_OK:
                // 成功接收到HELO命令的响应
                    if (sscanf(message, "250%*s"))
                    {
                            /*
                        if( query("smtpauthuser", CONFIG_D) )
                        {
                                // 配置为需要认证：发送认证命令
                                status = STATUS_START_AUTH;
                                write_message(fd, "AUTH LOGIN");
                                return;
                        }
                        */

                        // 配置为不需要认证，发送MAILFROM命令
                            status = STATUS_MAIL_FROM_OK;
                        write_message(fd, "MAIL FROM:<" + mail[MAIL_FROM] + ">");
                            return;
                    }
                break;

        case STATUS_START_AUTH:
                // 成功接收到AUTH命令的响应
                if (sscanf(message, "334%*s"))
                {
                        // 发送用户名
                        status = STATUS_USERNAME_SENT;
                        write_message(fd, encode64("lonely"));
                        return;
                }
                break;

        case STATUS_USERNAME_SENT:
                // 成功接收到发送用户名的响应
                if (sscanf(message, "334%*s"))
                {
                        // 发送口令
                        status = STATUS_PASSWORD_SENT;
                        write_message(fd, encode64("921121"));
                        return;
                }
                break;

        case STATUS_PASSWORD_SENT:
                // 成功接收到发送口令的响应
                if (sscanf(message, "235%*s"))
                {
                        // 发送MAILFROM命令
                        status = STATUS_MAIL_FROM_OK;
                        write_message(fd, "MAIL FROM:<" + mail[MAIL_FROM] + ">");
                            return;
                }
                break;

            case STATUS_MAIL_FROM_OK:
                // 成功接收到MAILFROM命令的响应
                    if (sscanf(message, "250%*s"))
                    {
                        // 发送RCPTTO命令
                            status = STATUS_RCPT_TO_OK;
                        write_message(fd, "RCPT TO:<" + mail[MAIL_RECEIVER] + ">");
                            return;
                    }
                    break;

            case STATUS_RCPT_TO_OK:
                // 成功接收到RCPTTO命令的响应
                    if (sscanf(message, "250%*s"))
                    {
                        // 发送DATA命令
                            status = STATUS_DATA_OK;
                        write_message(fd, "DATA");
                            return;
                    }
                    break;

            case STATUS_DATA_OK:
                // 成功接收到DATA命令的响应
                    if (sscanf(message, "354%*s"))
                    {
                        // 发送数据
                            status = STATUS_DATA_SENT;
                        write_message(fd, "Subject: " + mail[MAIL_TOPIC]);
                        write_message(fd, mail[MAIL_DATA] + "\r\n.");
                            return;
                    }
                    break;

        case STATUS_DATA_SENT:
                // 成功接收到发送数据的响应
                write_message(fd, "QUIT");
                    if (sscanf(message, "451%*s"))
                            log_file("mail", sprintf("%s Smtp Server error: %s.\n",
                                         log_time(), SMTP_SERVER));
                    else
                {
                        CHANNEL_D->do_channel(this_object(), "sys", "成功的发送了寄给<" +
                                              mail[MAIL_RECEIVER] +
                                              ">的邮件。");
                        // I will remove the mail in socket close call back fun
                        status = STATUS_FINISH;
                        return;
                }
                    break;
        }

        // 发送过程中产生了错误
        if (++(mail[MAIL_ERROR]) >= MAX_RETRY_COUNT)
        {
                log_file("mail", sprintf("%s Can not send mail <%s> to %s.\n",
                                         log_time(), mail[MAIL_TOPIC], mail[MAIL_RECEIVER]));
                remove_from_queue();
        }
        status = STATUS_INIT;
        socket_close(fd);
}

private void write_callback(int fd)
{
        can_write = 1;
        if (delay_message)
        {
                write_message(fd, delay_message);
                delay_message = 0;
        }
}

private void send_timeout(int fd)
{
        socket_close(fd);
        in_close_callback(fd);
}

private void in_close_callback(int fd)
{
        mixed *mail;

        remove_call_out("send_timeout");
        if (queue_pointer == next_mail &&
            status != STATUS_INIT)
                return;

        mail = mail_queue[queue_pointer];
        remove_from_queue();

        if (status == STATUS_FINISH)
        {
                // success send the mail
                status = STATUS_INIT;
                return;
        }

        status = STATUS_INIT;

        // error occur
        if (! mail) return;

        if (++(mail[MAIL_ERROR]) >= MAX_RETRY_COUNT)
        {
                log_file("mail", sprintf("%s Can not send mail: %s to %s.\n",
                                         log_time(), mail[MAIL_TOPIC], mail[MAIL_RECEIVER]));
        }
}

private int write_message(int fd, string arg)
{
        if (can_write)
        {
                socket_write(fd, arg + "\r\n");
        } else
                delay_message = arg;
        return 1;
}
