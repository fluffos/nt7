// socket_ob.c

#define TIMEOUT         120

nosave int socket_fd;
nosave mapping callback = allocate_mapping(0);

mixed query_funcs() { return callback; }

mapping dn2ip_tab = ([
        "news.sina.com.cn"      :   "61.135.152.78",
        "ent.sina.com.cn"       :   "61.135.152.80",
        "tech.sina.com.cn"      :   "61.135.152.85",
        "finance.sina.com.cn"   :   "61.135.153.184",
        "sports.sina.com.cn"    :   "61.135.153.179",
]);


private string DN2IP(string host)
{
        if (undefinedp(dn2ip_tab[host]))
                return "";

        return dn2ip_tab[host];
}

private int is_url(string fmt)
{
        array each_field = explode(fmt, ".");

        if (sizeof(each_field) < 4)
                return 0;

        foreach (string field in each_field)
        {
                foreach (int char in field)
                {
                        if (char < 'A' || char > 'z' ||
                            (char > 'Z' && char < 'a'))
                                return 0;
                }
        }
        return 1;
}

private int is_ip(string fmt)
{
        array each_field = explode(fmt, ".");

        if (sizeof(each_field) < 4)
                return 0;

        foreach (string field in each_field)
        {
                foreach (int char in field)
                {
                        if (char < '0' || char > '9')
                                return 0;
                }
        }
        return 1;
}

void create()
{
        seteuid(getuid());
        socket_fd = 0;
}

void receive_callback(mixed data)
{
        remove_call_out("time_out");
        evaluate(callback["rece_callback"], data, socket_fd);
         SOCKET_D->socket_close(socket_fd);
}

void close_callback(string msg)
{
        remove_call_out("time_out");
        evaluate(callback["stat_callback"], socket_fd);
        efun::socket_close(socket_fd);
        destruct(this_object());
}

void time_out()
{
        SOCKET_D->socket_close(socket_fd);
        // destruct(this_object());
}

int do_open(string host, int port, int mode, function rece_callback, function stat_callback)
{
        if (! host || ! port)
                return 0;
                
        if (! is_ip(host))
                host = DN2IP(host);
    
        callback["rece_callback"] = rece_callback;
        callback["stat_callback"] = stat_callback;
        socket_fd = SOCKET_D->socket_open(host, port, mode, (: receive_callback :), (: close_callback :));
        
        call_out((: time_out :), TIMEOUT);
        return socket_fd;
}

void do_send(mixed data)
{
        SOCKET_D->socket_send(socket_fd, data);
}