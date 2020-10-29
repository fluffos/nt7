// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// realnewsd.c 实时新闻系统

#include <ansi.h>
#include <net/socket.h>

#define TITLE                   0
#define HOST                    1
#define PAGE_URL                2
#define NEWS_URL                0
#define NEWS_FROM               1
#define NEWS_TIME               2
#define NEWS_DATA               3
#define REFRESH_TIME            21600
#define BROADCAST_TIME          600
#define DEFAULT_LIST_URL        "/news/index.shtml"
#define DEFAULT_NEWS_IP         "127.0.0.1"
#define DEFAULT_NEWS_URL        "rss.sina.com.cn"
#define ADDR_SYNTAX             "http://%s/%s"
#define CLEAR_URL(x)            replace_string(x, "\"", "")

//#define HTTP_GET_PAGE_REQUEST(_page_, _host_name_) "\n \
//GET " + _page_ + " HTTP/1.1\n \
//Accept: */ *\n \
//Accept-Language: zh-cn\n \
//Accept-Encoding: deflate\n \
//Accept-Charset: gb2312\n \
//Host: " + _host_name_ + "\n \
//Connection: Keep-Alive\n\n"

#define HTTP_GET_PAGE_REQUEST(_page_, _host_name_) "GET " + _page_ + " HTTP/1.1\r\nAccept: */*\r\nAccept-Language: zh-cn\r\nAccept-Encoding: deflate\r\nAccept-Charset: gb2312\r\nHost: " + _host_name_ + "\r\nConnection: Keep-Alive\r\n\r\n"

#define DEBUG(x) CHANNEL_D->channel_broadcast("nch", "REALNEWS_D 精灵："+(string)x)

void get_news_list(string url);
void get_each_news_data(int fd);

nosave mapping news_data;
nosave mapping news_list;
nosave mapping group_ids;
nosave mapping title_ids;

nosave int socket_fd;
nosave int get_news_event_id;
nosave int broadcast_event_id;
nosave mapping socket_obs;
nosave mapping get_each_news_times;

mapping query_news_data() {return news_data;}
mapping query_news_list() {return news_list;}
mapping query_group_ids() {return group_ids;}
mapping query_title_ids() {return title_ids;}

mapping query_get_news_times() {return get_each_news_times;}

mapping dn2ip_tab = ([
        "rss.sina.com.cn"       :   "127.0.0.1",
        "news.sina.com.cn"      :   "127.0.0.1",
        "ent.sina.com.cn"       :   "127.0.0.1",
        "tech.sina.com.cn"      :   "127.0.0.1",
        "finance.sina.com.cn"   :   "127.0.0.1",
        "sports.sina.com.cn"    :   "127.0.0.1",
        "mil.news.sina.com.cn"  :   "127.0.0.1",
]);

string DN2IP(string host)
{
        if (undefinedp(dn2ip_tab[host]))
                return "";

        return dn2ip_tab[host];
}

public string read_news_list()
{
        string list = sprintf("\n%4s%|12s%-48s\n%64'-'s\n", "编号", "类别", "标题", "");
        string * groups;
        string * titles;

        if ( !sizeof(news_list) || !sizeof(news_data) )
                return "当前没有可读新闻。\n";

        groups = keys(news_data);

        foreach (string gp in groups)
        {
                titles = keys(news_data[gp]);
                foreach (string tt in titles)
                {
                        /*************************************************************
                        if (!undefinedp(news_data[gp][tt]))
                                list += sprintf("%2d%2'0'd%|12s%-48s\n",
                                                group_ids[gp], title_ids[tt], gp, tt);
                        *************************************************************/
                        if (mb_query(gp + "/" + tt, news_data))
                                list += sprintf("%2d%2'0'd%|12s%-48s\n",
                                                group_ids[gp], title_ids[tt], gp, tt);
                }
        }

        return list;
}

public string read_news(string num)
{
        int group_id;
        int title_id;
        string group;
        string title;
        string * title_in_group;
        mixed data;

        if (! sscanf(num[0..0], "%d", group_id))
                return "新闻编号错误！\n";

        if (! sscanf(num[1..], "%d", title_id))
                return "新闻编号错误！\n";

        if (! sizeof(group_ids))
                return "新闻编号错误！\n";

        foreach (string gp, int n in group_ids)
        {
                if (n == group_id)
                {
                        group = gp;
                        break;
                }
        }

        title_in_group = keys(news_data[group]);

        foreach (string tt in title_in_group)
        {
                if (title_ids[tt] == title_id)
                {
                        title = tt;
                        break;
                }
        }

        /***********************************************
        if (undefinedp(news_data[group][title]))
        ***********************************************/
        if (! mb_query(group + "/" + title, news_data))
                return "新闻编号错误！\n";

        data = news_data[group][title];

        if (sizeof(data) > NEWS_DATA)
                return "\n" + HIY + sprintf("%|64s", title) + HIW + "\n" +
                        data[NEWS_URL] + NOR + data[NEWS_DATA];

        return "\n" + HIY + sprintf("%|64s", title) + HIW + "\n" +
                        data[NEWS_URL] + NOR + "\n\n新闻内容没有读取成功,请查看上面网址了解详情.\n\n";

}

void create_news_board()
{
        string * groups = keys(news_data);
        string * titles;
        int i = 1;

        group_ids = allocate_mapping(0);
        title_ids = allocate_mapping(0);

        foreach (string group in groups)
        {
                int j = 1;
                group_ids += ([ group : i ]);
                i++;
                titles = keys(news_data[group]);
                foreach (string tt in titles)
                {
                        title_ids += ([ tt : j ]);
                        j++;
                }
        }
}

void create_news_list()
{
        string *groups = keys(news_data);

        if( sizeof(groups) < 1 ) return;
        news_list = allocate_mapping(0);
        foreach (string group in groups)
        {
                foreach (string title in keys(news_data[group]))
                {
                        news_list += ([title : news_data[group][title][NEWS_URL]]);
                }
        }
}

string parse_news_data(string data)
{
        string temp;
        string text = "";
        int i, a, b, c, d;
        int data_size, text_flag = 0, el_flag = 0;

        a = strsrch(data, "<!-- publish_helper name=");
        b = strsrch(data, "<!-- 分享 begin -->");

        data = data[a..b];
        c = strsrch(data, "<!--NEWSZW_HZH_BEGIN-->");
        d = strsrch(data, "<!--NEWSZW_HZH_END-->");
        if (c > 0 && d > 0)
                data = data[0..c] + data[d..];

        data_size = sizeof(data);

        i = 0;
        reset_eval_cost();
        while (i++ < data_size)
        {
                reset_eval_cost();
                temp = data[i-1..i-1];
                if (temp == "<")
                {
                        if ((data[i] == 'p' || data[i] == 'P') && data[i+1] == '>')
                        {
                                i += 2;
                                text += "\n";
                                text_flag = 1;
                        } else
                        if (data[i] == '/')
                        {
                                if(data[i+1] == 'p' && data[i+2] == '>')
                                {
                                        i += 3;
                                        text_flag = 0;
                                }
                                else
                                {
                                        while(data[i++] != '>') {}
                                }

                        } else
                        if ((data[i] == 'b' || data[i] == 'B') && data[i+1] == '>')
                        {
                                i += 2;
                                text += "\n";
                        } else
                        if (text_flag)
                                el_flag = 1;
                } else
                if (temp == ">")
                {
                        if (el_flag)
                                el_flag = 0;
                }
                else
                {
                        if (text_flag && ! el_flag)
                                text += temp;
                }
        }

        return sort_msg(text);
}

void get_each_news_status(int fd, string msg)
{
        // 返回错误的信息
        if (fd && !undefinedp(socket_obs[fd]))
                DEBUG(sprintf("读取单独新闻『%s』线程状况：%s\n",
                              socket_obs[fd][TITLE], msg));
        else
                DEBUG(sprintf("读取单独新闻线程状况：%s\n", msg));
}

void get_each_news_rece(int fd, mixed data)
{
        /*
        if (undefinedp(news_data["temp"]) )
                news_data["temp"] = ([]);

        if (undefinedp(news_data["temp"][fd]))
                news_data["temp"][fd] = data;
        else
                news_data["temp"][fd] += data;
        */
        // 获取主页某一个新闻内容信息放入news_data["temp"]["fd"]中

        mb_set("temp/" + fd, mb_query("temp/" + fd, news_data) + data, news_data);
}

void get_each_news_close(int fd)
{
        // parse_each_news();
        string title;
        string group_name;
        string news_html_page;
        string * groups = keys(news_data);
        string * news_info;

        if (undefinedp(socket_obs[fd]))
        {
                socket_close(fd);
                return;
        }

        title = socket_obs[fd][TITLE];

        foreach (string group in groups)
                if (! undefinedp(news_data[group][title]))
                {
                        // 获取新闻类别名
                        group_name = group;
                        break;
                }

        if (! sizeof(group_name))
        {
                socket_close(fd);
                map_delete(socket_obs, fd);
                return;
        }

        // news_info = news_data[group_name][title];
        news_info = mb_query(group_name + "/" + title, news_data);
        // news_html_page = news_data["temp"][fd];
        news_html_page = mb_query("temp/" + fd, news_data);

        if (! sizeof(news_html_page) || strsrch(news_html_page, "</html>") < 0)
        {
                // 获取新闻失败则重新尝试
                get_each_news_data(fd);
                socket_close(fd);
                return;
        }

        news_html_page = parse_news_data(news_html_page);
        news_info += ({ news_html_page });

        // 将新闻内容加到news_data里
        // news_data[group_name][title] = news_info;
        mb_set(group_name + "/" + title, news_info, news_data);
        // map_delete(news_data["temp"], fd);
        mb_delete("temp/" + fd, news_data);

        socket_close(fd);
        map_delete(socket_obs, fd);

        if (! mapp(socket_obs) || ! sizeof(socket_obs))
                mb_delete("temp", news_data);
}

void get_each_news_data(int fd)
{
        string page_url, purl;
        string host, hostip;
        int    socket_ob_fd;
        mixed  socket_data;

        if( fd ) // 读取指定fd的news，主要出现在读取不成功时。
        {
                socket_data = socket_obs[fd];

                purl = socket_data[PAGE_URL];
                if( !undefinedp(get_each_news_times[purl]) )
                {
                        // 再次读取不成功的话则放弃读取
                        map_delete(socket_obs, fd);
                        return;
                }

                get_each_news_times += ([ purl : 1 ]);

                if( sscanf(socket_data[HOST], "%*d.%*d.%*d.%*d") == 4 )
                        hostip = socket_data[HOST];
                else
                        hostip = DN2IP(socket_data[HOST]);

                socket_ob_fd = SOCKET_D->socket_open(hostip, 80, STREAM,
                        (: get_each_news_rece :), (: get_each_news_close :), (: get_each_news_status :));

                if (socket_ob_fd < 0)
                {
                        map_delete(socket_obs, fd);
                        return;
                }

                socket_obs += ([ socket_ob_fd : ({ socket_data[TITLE], socket_data[HOST], socket_data[PAGE_URL] }) ]);
                SOCKET_D->socket_send(socket_ob_fd, HTTP_GET_PAGE_REQUEST(socket_data[PAGE_URL], socket_data[HOST]));
                map_delete(socket_obs, fd);
                return;
        }

        foreach( string title, string url in news_list )
        {
                reset_eval_cost();
                if( !sizeof(url) ) continue;

                sscanf(url, ADDR_SYNTAX, host, page_url);

                if( !sizeof(host) )
                        host = DEFAULT_NEWS_URL;

                if( !sizeof(page_url) )
                        continue;

                if( sscanf(host, "%*d.%*d.%*d.%*d") == 4 )
                        hostip = host;
                else
                        hostip = DN2IP(host);

                page_url = "/" + page_url;
                socket_ob_fd = SOCKET_D->socket_open(hostip, 80, STREAM,
                        (: get_each_news_rece :), (: get_each_news_close :), (: get_each_news_status :));

                if (socket_ob_fd < 0)
                        break;

                socket_obs += ([ socket_ob_fd : ({ title, host, page_url }) ]);
                SOCKET_D->socket_send(socket_ob_fd, HTTP_GET_PAGE_REQUEST(page_url, host));
        }
}

void parse_group_list()
{
        string temp;
        string group_part;
        string group_name;
        string body_part;
        string a_news_page_url;
        string a_news_title;
        string a_news_from;
        string a_news_time;

        if (! (temp = mb_query("temp/group", news_data)))
                return;
        
        //body_part = temp[strsrch(temp, "<channel>")..strsrch(temp, "</channel>")];
        body_part = temp;
        
        while(sscanf(body_part, "%*s<item>%s</item>%s", group_part, body_part) > 1)
        {
                reset_eval_cost();

                group_part = to_default_encoding(group_part, "utf-8");
                //DEBUG(sprintf("%s\n", group_part));

                sscanf(group_part, "%*s<title>%*s<![CDATA[%s]]>%*s</title>%*s", a_news_title);
                sscanf(group_part, "%*s<link>%*s=%s</link>%*s", a_news_page_url);
                sscanf(group_part, "%*s<category>%*s<![CDATA[%s]]>%*s</category>%*s", group_name);
                sscanf(group_part, "%*s<author>%s</author>%*s", a_news_from);
                sscanf(group_part, "%*s<pubDate>%s</pubDate>%*s", a_news_time);

                //a_news_title = replace_string(a_news_title, "/", "／");
                // news_data[group_name][a_news_title] = ({a_news_page_url, a_news_from, a_news_time});
                mb_set(group_name + "/" + a_news_title, ({ a_news_page_url, a_news_from, a_news_time }), news_data);

                //DEBUG(sprintf("%s-%s:%O\n", group_name, a_news_title, ({ a_news_page_url, a_news_from, a_news_time })));
        }
        
}

void get_group_list_rece(int fd, mixed data)
{
        // 获取主页所有内容信息放入news_data["temp"][group"]中
        mb_set("temp/group", mb_query("temp/group", news_data) + data, news_data);
        //DEBUG(sprintf("获取主页所有内容放入news_data[temp][group]信息：%O\n", data));
}

void get_group_list_close(int fd)
{
        parse_group_list();
        // map_delete(news_data["temp"], "group");
        mb_delete("temp/group", news_data);

        socket_close(fd);

        create_news_list();
        get_each_news_data(0);
        create_news_board();

        broadcast_event_id = SCHEDULE_D->set_event(BROADCAST_TIME, 1,
                this_object(), "broadcast_news");
}

void parse_news_list()
{
        mapping group_list = allocate_mapping(0);
        string temp;
        string group_part;
        string group_name;
        string body_part;
        string a_news_page_url;
        string a_news_title;
        string a_news_from;
        string a_news_time;
        int i;
        string page_url, purl;
        string host, hostip;
        int    socket_ob_fd;
        mixed  socket_data;

        // 将获取的主页内容进行筛选归类存放到news_data[group_name][title]
        // if (! (temp = news_data["temp"]["list"]))
        if (! (temp = mb_query("temp/list", news_data)))
                return;

        body_part = temp[strsrch(temp, "<!-- 右侧频道内容开始-->")..strsrch(temp, "<!-- 右侧频道内容结束-->")];

        reset_eval_cost();
        //&nbsp;&nbsp;<a href="http://rss.sina.com.cn/news/marquee/ddt.xml" class="f14"><font color="#000000">国内要闻</font></a></span></td>
        while(sscanf(body_part, "%*s&nbsp;&nbsp;<a href=\"%s\" class=\"f14\"><font color=\"#000000\">%s</font></a></span></td>%s", a_news_page_url, group_name, body_part) > 2)
        {
                reset_eval_cost();

                if( group_name != "国内要闻" && group_name != "国际要闻" && group_name != "社会新闻" && group_name != "时政要闻" )
                        continue;
                        
                group_list += ([group_name : a_news_page_url]);
        }
        DEBUG(sprintf("%O\n", group_list));
        
        foreach( string title, string url in group_list )
        {
                reset_eval_cost();
                if( !sizeof(url) ) continue;

                sscanf(url, ADDR_SYNTAX, host, page_url);

                if( !sizeof(host) )
                        host = DEFAULT_NEWS_URL;

                if( !sizeof(page_url) )
                        continue;

                if( sscanf(host, "%*d.%*d.%*d.%*d") == 4 )
                        hostip = host;
                else
                        hostip = DN2IP(host);

                page_url = "/" + page_url;
                socket_ob_fd = SOCKET_D->socket_open(hostip, 80, STREAM,
                        (: get_group_list_rece :), (: get_group_list_close :), (: get_each_news_status :));

                if (socket_ob_fd < 0)
                        continue;

                socket_obs += ([ socket_ob_fd : ({ title, host, page_url }) ]);
                SOCKET_D->socket_send(socket_ob_fd, HTTP_GET_PAGE_REQUEST(page_url, host));
        }
}

void get_news_list_rece(int fd, mixed data)
{
        /*
        if (undefinedp(news_data["temp"]["list"]))
                news_data["temp"]["list"] = data;
        else
                news_data["temp"]["list"] += data;
        */
        // 获取主页所有内容信息放入news_data["temp"]["list"]中
        mb_set("temp/list", mb_query("temp/list", news_data) + data, news_data);
        //DEBUG(sprintf("获取主页所有内容放入news_data[temp][list]信息：%O\n", data));
}

void get_news_list_close(int fd)
{
        parse_news_list();
        // map_delete(news_data["temp"], "list");
        mb_delete("temp/list", news_data);

        socket_close(fd);
        /*
        create_news_list();
        get_each_news_data(0);
        create_news_board();

        broadcast_event_id = SCHEDULE_D->set_event(BROADCAST_TIME, 1,
                this_object(), "broadcast_news");
        */
}

void get_news_list(string url)
{
        socket_fd = SOCKET_D->socket_open(DEFAULT_NEWS_IP, 80, STREAM,
                (: get_news_list_rece :),(: get_news_list_close :), (: get_each_news_status :));

        if (socket_fd >= 0)
        {
                /*
                if (broadcast_event_id)
                        SCHEDULE_D->delete_event(broadcast_event_id -1);
                */
                SOCKET_D->socket_send(socket_fd, HTTP_GET_PAGE_REQUEST(url, DEFAULT_NEWS_URL));
        }
}

void broadcast_news()
{
        string * groups;
        string news_group;
        string * titles_in_group;
        string news_title;

        if (! sizeof(news_data))
                return;

        groups = keys(news_data);
        news_group = groups[random(sizeof(groups))];

        if (! sizeof(news_data[news_group]))
                return;

        titles_in_group = keys(news_data[news_group]);
        news_title = titles_in_group[random(sizeof(titles_in_group))];

        // if (! news_data[news_group][news_title])
        if (! mb_query(news_group + "/" + news_title, news_data))
        {
                // broadcast_news();
                return;
        }
        CHANNEL_D->channel_broadcast("news", sprintf(WHT "【%s】%s%3s%s%3s(新闻编号%d%2'0'd)\n" NOR,
                                    news_group, news_title, "", news_data[news_group][news_title][NEWS_TIME], "",
                                    group_ids[news_group], title_ids[news_title]));
        /*
        message("realnews", sprintf(WHT "【%s】%s%3s%s%3s(新闻编号%d%2'0'd)\n" NOR,
                                    news_group, news_title, "", news_data[news_group][news_title][NEWS_TIME], "",
                                    group_ids[news_group], title_ids[news_title]),
                                    filter_string *(users(), (: !$1->query("env/no_realnews") :)));
        */
}

void refresh_news()
{
        socket_obs = allocate_mapping(0);
        news_data = allocate_mapping(0);
        get_each_news_times = allocate_mapping(0);
        get_news_list(DEFAULT_LIST_URL);
}

void create()
{
        seteuid(ROOT_UID);

        refresh_news();
        get_news_event_id = SCHEDULE_D->set_event(REFRESH_TIME, 1,
                this_object(), "refresh_news");
}

string query_name()
{
        return "真实新闻系统(REALNEWS_D)";
}
