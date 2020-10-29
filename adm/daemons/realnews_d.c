#include <net/socket.h>
#include <socket_err.h>

#define monitor(x)		CHANNEL_D->channel_broadcast("nch", "REALNEWS_D: " + x)
#define PROCESS_URL		0
#define PROCESS_FLAG		1


#define ADDR_SYNTAX		"http://%s/%s"
#define UPDATE_TIME		30*60	// 每 30 分钟更新
#define PROCESS_TIMEOUT		30
#define RESOLVE_TIMEOUT		10
#undef DEBUG

/* Prototype */
void socket_shutdown(int fd);
void do_again();
void do_next();
void get_url(string url);
void process_news(string msg);
varargs void get_news(string url, string type, int flag);

string html_remove(string str);
string html_normalize(string str);

class socket_info
{
    int received, socket_fd, resolved, connect_port;
    int write_fd;
    string connect_ip, get_path;
    string write_buffer, read_buffer;
}

class process_info
{
    string url, type;
    int flag;
    string encoding;
}

class socket_info skt_inf = new(class socket_info);
class process_info current_process = new(class process_info);
class process_info *process_queue = allocate(0);

nosave int resolve_handle, connect_handle, is_process;
nosave mapping news = allocate_mapping(0);
nosave mapping resolve_catch = allocate_mapping(0);
nosave mapping retry_count = allocate_mapping(0);
nosave mapping name_alias = ([
  /*
    "thg"         : "Tom's Hardware Guide",
    "yahoo"		: "Yahoo!",
    "pchome"		: "PC Home",
    "yam"		: "蕃薯藤",
    "bahamut"	:	"Bahamut",
  */
  "udn"      : "联合新闻网",
]);

void create()
{
    // Yam
    //SCHEDULE_D->set_event(60*60*1, 1, this_object(), "get_news", "http://news.yam.com/all/real/index.html", "yam", -1);
    // PChome
    //SCHEDULE_D->set_event(UPDATE_TIME, 1, this_object(), "get_news", "http://news.pchome.com.tw/include/online_news.html", "pchome", -1, "big5");
    // Yahoo
    //SCHEDULE_D->set_event(60*60*1, 1, this_object(), "get_news", "http://tw.news.yahoo.com/realtime/0.html", "yahoo", -1, "big5");
    // Bahamut
    //SCHEDULE_D->set_event(60*60*3, 1, this_object(), "get_news", "http://gnn.gamer.com.tw/", "bahamut", -1, "UTF-8");
    // Tom's Hardware Guide
    //SCHEDULE_D->set_event(60*60*12, 1, this_object(), "get_news", "http://www.thg.com.tw/STInforNews/STContList.asp?nsp=Q", "thg", -1, "big5");

    //udn 联合新闻网 by Msr
    SCHEDULE_D->set_event(UPDATE_TIME, 1, this_object(), "get_news", "http://udn.com/NEWS/BREAKINGNEWS/", "udn", -1);

    // 定时播报新闻
    SCHEDULE_D->set_event(60*60, 1, this_object(), "channel_news");
}
void channel_news()
{
    int i;
    string type, title;

    if( !(i = sizeof(news)) ) return;
    i = random(i);
    type = keys(news)[i];
    if( !(i = sizeof(news[type][0])) ) return;
    i = random(i);

    title = news[type][0][i];
    CHANNEL_D->channel_broadcast("news", name_alias[type] + ": " + title);
    return;
}

void socket_send(int fd, mixed msg)
{
    int res;

#ifdef DEBUG
    monitor("送出讯息: " + msg);
#endif

    if( !msg || msg == "" ) return; 
    // 尚未收到 socket write callback 前，将欲传送的讯息存入 buffer
    if( !skt_inf->write_fd )
    {
        if( !skt_inf->write_buffer ) skt_inf->write_buffer = "";
        skt_inf->write_buffer += msg;
        return;
    }
    // 如果 buffer 中有讯息尚未送出，则与本次讯息同时送出
    if( skt_inf->write_buffer )
    {
        skt_inf->write_buffer += msg;
        res = socket_write(fd, skt_inf->write_buffer);
    }
    else res = socket_write(fd, msg);

    switch(res) {

    case EESUCCESS:		/* 成功 */
    case EECALLBACK:	/* 等待完成 */
        skt_inf->write_buffer = 0;
        break;
    case EEALREADY:		/* 程序已进行 */
    case EEWOULDBLOCK:	/* 程序停滞 */
    case EESEND:		/* 传送资料错误 */
        if( !skt_inf->write_buffer ) skt_inf->write_buffer = msg;
        call_out((: socket_send :), 1, fd, "");
        break;
    default:		/* 其他错误 */
        monitor("socket_send: " + socket_error(res));
        // try again
        socket_shutdown(fd);
        do_again();
        do_next();
        break;
    }
}

void receive_data(int fd, string msg)
{ 
    if( !skt_inf->read_buffer ) skt_inf->read_buffer = "";
    skt_inf->read_buffer += msg;
    //monitor(msg);
}

void write_data(int fd)
{
    skt_inf->write_fd = fd;
    remove_call_out(connect_handle);
    // 如果收到 socket write callback 时
    // buffer 内有讯息未传送则立即传送，并清除 buffer
    if( skt_inf->write_buffer )
    {
        socket_write(fd, skt_inf->write_buffer);
        skt_inf->write_buffer = 0;
    }
}

void connection_close(int fd)
{

#ifdef DEBUG
    monitor("Connection closed by " + skt_inf->connect_ip +".\n");
#endif

    process_news(skt_inf->read_buffer);
    socket_shutdown(fd);
    do_next();
}

void connect_timeout(int fd)
{
    monitor("connect: Unable to connect to remote host: Connection timeout\n");
    socket_shutdown(fd);
    do_again();
    do_next();
}

void do_connect()
{
    int res;
    string addr;

    remove_call_out(resolve_handle);

    skt_inf->socket_fd = socket_create(STREAM, (: receive_data :), (: connection_close :));

    if( skt_inf->socket_fd < 0 )
    {
        monitor("do_connect: Unable to create socket: " + socket_error(skt_inf->socket_fd) + "\n");
        is_process = 0;
        do_again();
        do_next();
        return;
    }
    addr = skt_inf->connect_ip + " " + skt_inf->connect_port;
    res = socket_connect(skt_inf->socket_fd, addr, (: receive_data :), (: write_data :));
    if( res != EESUCCESS )
    {
        monitor("do_connect: Unable to connect remote host: " + socket_error(res) + "\n");
        socket_shutdown(skt_inf->socket_fd);
        do_again();
        do_next();
        return;
    }
    socket_send(skt_inf->socket_fd, sprintf("GET "ADDR_SYNTAX"\n\n", skt_inf->connect_ip, skt_inf->get_path));
    connect_handle = call_out((: connect_timeout :), PROCESS_TIMEOUT, skt_inf->socket_fd);
}

void socket_shutdown(int fd)
{
    socket_close(fd);
    skt_inf->received = 0;
    skt_inf->socket_fd = 0;
    skt_inf->write_fd = 0;
    skt_inf->resolved = 0;
    skt_inf->connect_port = 0;
    skt_inf->connect_ip = 0;
    skt_inf->read_buffer = 0;
    skt_inf->write_buffer = 0;
    is_process = 0;
    return;
}

void resolve_timeout()
{
    monitor("resolve: Unable to resolve remote host: Timeout.\n");
    is_process = 0;
    skt_inf->resolved = 0;

    do_again();
    do_next();
}

void resolve_callback(string addr, string ip, int key)
{
    if( key != skt_inf->resolved ) return;
    if( !addr || !ip )
    {
        monitor("resolve: " + (ip || addr) + " - Unknown host.\n");
        is_process = 0;
        skt_inf->resolved = 0;
        do_next();
        return;
    }
    resolve_catch[addr] = ip;
    skt_inf->connect_ip = ip;
    do_connect();
}

varargs void get_news(string url, string type, int flag, string encoding)
{
    class process_info process = new(class process_info);

    process->url = url;
    process->flag = flag;
    process->type = type;
    process->encoding = encoding;
    process_queue += ({ process });
    if( !is_process )
    {
        is_process = 1;
        do_next();
    }
}
void do_again()
{
    if( retry_count[current_process->url] > 3 ) return;
    get_news(current_process->url, current_process->type, current_process->flag);
    retry_count[current_process->url]++;
}

void do_next()
{
    if( !sizeof(process_queue) )
    {
        monitor("已取得所有新闻");
        return;
    }
    current_process = process_queue[0];
    process_queue = process_queue[1..];
    call_out((: get_url :), 1, current_process->url);
    return;
}

void get_url(string url)
{
    int port;
    string host, path;

    is_process = 1;

    sscanf(url, ADDR_SYNTAX, host, path);
    if( !host ) return;
    if( !port ) port = 80;
    skt_inf->connect_port = port;
    skt_inf->get_path = path;

    // realnews_d 的 resolve 好像怪怪的
    // 先直接给 ip 好了 by Msr
    if( host == "udn.com" )
        host = "210.244.31.154";

    // resolve catch
    if( !undefinedp(resolve_catch[host]) )
    {
        host = resolve_catch[host];
    }

    if( sscanf(host, "%*d.%*d.%*d.%*d") != 4 )
    {
        monitor(sprintf("解析主机位置: %O", host));
        skt_inf->resolved = resolve(host, (: resolve_callback :));
        resolve_handle = call_out((: resolve_timeout :), RESOLVE_TIMEOUT);
        return;
    }

    skt_inf->connect_ip = host;
    do_connect();
    return;
}

void process_news(string msg)
{
    int i, flag;
    string *lines, time, hlink;
    //mixed *news_buffer = allocate(2);

    flag = current_process->flag;

    if( !msg )
    {
        monitor("错误: 未取得任何讯息");
        return;
    }

    if( flag < 0 )
        monitor("取得 " + current_process->type + " 即时新闻清单中 ...");
#ifdef DEBUG
    else
        monitor("已下载 " + current_process->type + " 新闻文章，尚有 " + sizeof(process_queue) + " 个执行序");
#endif



    if( current_process->type == "yahoo" )
    {
        if( flag < 0 ) // Get list
        {
            mixed *temp;

            //monitor(msg);
            lines = explode(msg, "\n");
            lines = regexp(lines, "<a href="); // Catch All Hyperlink 

            temp = allocate(2);
            temp[0] = allocate(0);
            temp[1] = allocate(0);
            foreach(string line in lines)
            {
                if( sscanf(line, "%*s<a href=\"%s\"><big>%s</big></a><font%*s><small>(%s)</small>%*s", hlink, line, time) != 6 ) continue;
                temp[0] += ({ sprintf("%s (%s)", line, time) });
                temp[1] += ({ "http://tw.news.yahoo.com" + hlink });
                get_news(temp[1][i], current_process->type, i);
                i++;
            }
            if( i > 0 ) news[current_process->type] = temp;
            return;
        }
        else
        {
            string article = "", head, tail;
            lines = explode(msg, "\n");
            lines = regexp(lines, "<big>"); // Catch
            foreach(string line in lines)
            {
                if( sscanf(line, "<big>%s</big><br><br>", line) == 0 ) continue;
                if( sscanf(line, "%s<span class=sbody>%*s</span>%s", head, tail) == 3 ) line = head + tail;
                if( sscanf(line, "%s<span class=sbody>%*s", head) == 2 ) line = head;
                if( sscanf(line, "%*s</span>%s", tail) == 2 ) line = tail;
                article += line + "\n\n";
            }
            news[current_process->type][1][flag] = article;
            return;
        }
    }
    if( current_process->type == "thg" )
    {
        if( flag < 0 )
        {
            //msg = html_normalize(msg);
            lines = explode(msg, "<td class=CDate>");
            lines = regexp(lines, "CTitleB"); // Catch All Hyperlink 
            news[current_process->type] = allocate(2);
            news[current_process->type][0] = allocate(0);
            news[current_process->type][1] = allocate(0);

            foreach(string line in lines)
            {
                if( sscanf(line, "%s<tr><td class=CTitleB><a href='%s'>%s</a><tr>%*s", time, hlink, line) != 4 ) continue;
                line = replace_string(line, "<br>", "");
                news[current_process->type][0] += ({ sprintf("%s (%s)", line, time) });
                news[current_process->type][1] += ({ "http://www.thg.com.tw/STInforNews/" + hlink });
                get_news(news[current_process->type][1][i], current_process->type, i);
                i++;
            }

            return;
        }
        else
        {
            msg = html_normalize(msg);
            sscanf(msg, "%*s<td class=ctext>%s<tr>%*s", msg);
            //monitor(msg);
            msg = html_remove(msg);
            news[current_process->type][1][flag] = msg;
            return;
        }
    }
    if( current_process->type == "pchome" )
    {
        if( flag < 0 )
        {
            lines = explode(msg, "\n");
            lines = regexp(lines, "= .<a href"); // Catch All Hyperlink 

            news[current_process->type] = allocate(2);
            news[current_process->type][0] = allocate(0);
            foreach(string line in lines)
            {
                sscanf(line, "%*s>%s</a>%*s(%s)%*s", line, time);
                news[current_process->type][0] += ({ sprintf("%s (%s)", line, time) });
                i++;
            }
            return;
        }
    }
    if( current_process->type == "bahamut" )
    {
        if( flag < 0 )
        {
            lines = explode(msg, "\n");
            lines = regexp(lines, "td nowrap"); // Catch All Hyperlink

            news[current_process->type] = allocate(2);
            news[current_process->type][0] = allocate(0);

            foreach(string line in lines)
            {
                sscanf(line, "<tr><td width=%*s><img src=%*s width=%*s height=%*s></td><td nowrap><a class=%*s href=%*s>%s</a>%*s</td></tr><tr>%*s</td></tr>", line);               

                line = to_default_encoding(line, current_process->encoding);

                if( stringp(line) )
                {
                    catch(news[current_process->type][0] += ({ line }));
                    i++;
                }
            }
            return;
        }
    }
    if( current_process->type == "yam" )
    {
        if( flag < 0 )
            monitor(msg);
    }

    if( current_process->type == "udn" )
    {
        if( flag < 0 ) // Get list
        {
            mixed *temp;

            lines = explode(msg, "\n");
            lines = regexp(lines, "<a href="); // Catch All Hyperlink 

            temp = allocate(2);
            temp[0] = allocate(0);
            temp[1] = allocate(0);
            foreach(string line in lines)
            {
                if( sscanf(line, "%*s<a href=\"%s\" target=\"_blank\" >%s</a></td>", hlink, line) != 3 ) continue;
                if(member_array( line, temp[0] ) != -1 ) continue;

                temp[0] += ({ sprintf("%s", line) });
                temp[1] += ({ hlink });
                //get_news(temp[1][i], current_process->type, i);
                i++;
            }
            if( i > 0 ) news[current_process->type] = temp;
            return;
        }
    }
}

string html_normalize(string str)
{
    string head, tag, tail, res = "";

    while(sscanf(str, "%s<%s>%s", head, tag, tail) == 3)
    {
        res += sprintf("%s<%s>", head, lower_case(tag));
        str = tail;
    }
    res += str;
    return res;
}
string html_remove(string str)
{
    string head, tag, tail;

    while(sscanf(str, "%s<%s>%s", head, tag, tail) == 3)
    {
        switch(lower_case(tag))
        {
        case "br":	tag = "\n"; break;
        case "p":	tag = "\n\n"; break;
        default:	tag = "";
        }
        str = head + tag + tail;
    }
    str = replace_string(str, "&amp;", "&");
    str = replace_string(str, "&lt;", "<");
    str = replace_string(str, "&gt;", ">");
    str = replace_string(str, "&nbsp;", ">");
    return str;
}

string *query_news(int n)
{
    string *res = allocate(0);
    int j;
    foreach(string type, array data in news)
    {
        j = n;
        if( j > sizeof(data[0]) ) j = sizeof(data[0]);
        for(int i=0; i<j; i++)
        {
            res += ({ sprintf("%s-%s", type, data[0][i]) });
        }
    }
    return res;
}
string *query_news_titles(string type)
{
    if( undefinedp(news[type]) ) return ({ "尚未取得新闻资讯" });
    return news[type][0];
}
string *query_news_articles(string type)
{
    if( undefinedp(news[type]) ) return ({ "尚未取得新闻资讯" });
    return news[type][1];
}
string query_news_article(string type, int i)
{
    if( undefinedp(news[type]) ) return "没有这个类别的新闻";
    if( i < 0 || i >= sizeof(news[type][1]) ) return "没有这个新闻文章";
    return news[type][1][i];
}
mixed *query_process_queue()
{
    return process_queue;
}
string query_name()
{
    return "真实新闻系统(REALNEWS_D)";
}
