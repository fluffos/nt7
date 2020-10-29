// fingerd.c

#include <net/dns.h>
#include <net/messaged.h>
#include <ansi.h>

#include <mudlib.h>
#include "/adm/etc/database.h"

int sort_by_ip(object ob1, object ob2);

void create() { seteuid( getuid() ); }

int sort_by_ip(object ob1, object ob2)
{
        string ip1, ip2;

        if (! wizardp(ob1) && wizardp(ob2))
                return -1;

        if (wizardp(ob1) && ! wizardp(ob2))
                return 1;

        if (interactive(ob1) && ! interactive(ob2))
                return -1;

        if (! interactive(ob1) && interactive(ob2))
                return 1;

        if (interactive(ob1) && interactive(ob2))
        {
                ip1 = query_ip_number(ob1);
                ip2 = query_ip_number(ob2);
                if (ip1 != ip2)
                        return strcmp(ip1, ip2);
        }

        return strcmp(getuid(ob1), getuid(ob2));
}

string age_string(int time)
{
        int month, day, hour, min, sec;

        sec = time % 60;
        time /= 60;
        min = time % 60;
        time /= 60;
        hour = time % 24;
        time /= 24;
        day = time % 30;
        month = time / 30;
        return (month?month + "m":"") + (day?day + "d":"") +
        (hour?hour + "h":"") + min + "m";
}

string user_list(object *ob, int flag)
{
        object me;
        string msg;
        string ipname;
        int admin;
        int i;

        if (! ob || ! sizeof(ob))
                return "没有任何符合条件的玩家。\n";
        me = this_player();
        admin = me->is_admin() || (SECURITY_D->query_site_privilege("finger") == "enable");
        msg = "————————————————————————"
              "—————————\n" +
              BBLU WHT "姓名          帐号          年龄          发呆   连线             \n" NOR +
              "————————————————————————"
              "—————————\n";
        for(i = 0; i < sizeof(ob); i++)
        {
                if (me && ! me->visible(ob[i])) continue;
                //ipname = query_ip_name(ob[i]);
                ipname = admin ? query_ip_number(ob[i]) : "--------";
                msg = sprintf("%s%s%-14s%s%-14s%-14s%s%-7s" NOR "%s\n",
                        msg, (ob[i]->name() != ob[i]->name(flag) ? HIM : NOR),
                        ob[i]->name(flag),NOR,query("id", ob[i]),
                        age_string(query("mud_age", ob[i])),
                        (interactive(ob[i])?((query_idle(ob[i]) >= 120)?HIG:NOR):query("doing", ob[i]) == "closed"?HIY:HIR),
                        (interactive(ob[i])?(query_idle(ob[i])+"s"):query("doing", ob[i]) == "closed"?"闭关":(query("doing", ob[i]) == "scheme"?"计划":"断线")),ipname);
        }

        msg += "————————————————————————"
               "—————————\n";
        return msg;
}

varargs string finger_all(int idle)
{
        object *ob,*login_ob;
        string msg, fip;
        int i;
        int admin;
        object me;

        me = this_player();
        ob = users();
        msg = "";
        admin = me->is_admin() || (SECURITY_D->query_site_privilege("finger") == "enable");
        if (wiz_level(me) < 3)  // player finger
        {
                for (i = 0; i < sizeof(ob); i++)
                {
                        if (me && ! me->visible(ob[i])) continue;
                        msg = sprintf("%s%-14s%-14s%-14s\n",
                                msg,query("name", ob[i]),query("id", ob[i]),
                                (interactive(ob[i]) ? (query_idle(ob[i]) + "s") : HIR "断线中" NOR));
                }
                return "◎ " + MUD_NAME + "\n" +
                       "——————————————————\n"
                       + "姓名          帐号          发呆\n" +
                       "——————————————————\n"
                       + msg +
                       "——————————————————\n";
        } else         // wizard finger
        {
                string *counter;
                string ipname;
                int pcnt;
                int lcnt;

                pcnt = 0;
                lcnt = 0;
                counter = ({ });
                if (idle)
                        ob = filter_array(ob, (: interactive($1) && !query_idle($1) :) );
                if (admin)
                        ob = sort_array(ob, (: sort_by_ip :));
                for(i = 0; i < sizeof(ob); i++)
                {
                        if (me && ! me->visible(ob[i])) continue;
                        //ipname = query_ip_name(ob[i]);
                        ipname = query_ip_number(ob[i]);
                        if (environment(ob[i]))
                        {
                                pcnt++;
                                if (interactive(ob[i]) &&
                                    member_array(ipname, counter) == -1 )
                                        counter += ({ ipname });
                        }
                }

                login_ob = children("/clone/user/login");
                login_ob = filter_array(login_ob, (: query_ip_number($1) :) );
                lcnt = sizeof(login_ob);

                msg = WHT "◎ " + MUD_NAME + "\n" NOR + user_list(ob, 1) +
                      sprintf("%d个在线玩家来自%d个不同的地点，"
                              "%s玩家进入游戏中。\n\n",
                              pcnt, sizeof(counter),
                              lcnt ? (string) lcnt + "个" : "目前没有");
                return msg;
        }
}

// convert ip number into the type which database
// can understand
string resolve_ip_number(string ip_number)
{
        string part, *parts;
        string full;

        parts = explode(ip_number, ".");
        full = "";
        foreach (part in parts)
                full += replace_string(sprintf("%3s", part), " ", "0");
        return full;
}

varargs string finger_user(string name, mixed me)
{
        object ob, body;
        string msg, mud, where;
        int public_flag;
        string cname;
        string email, *ret;
        string sql, ip_number;
        string info;
        string addr;
        string *res;
        int flag;
        int admin;
        object *uob;
        int same;
        int i;

        if (! me) me = this_player();
        if (sscanf(name, "%s@%s", name, mud) == 2)
                if (msg = GFINGER_Q->send_gfinger_q(mud, name, me))
                        return msg;

        admin = me->is_admin() || (SECURITY_D->query_site_privilege("finger") == "enable");
        ob = new(LOGIN_OB);
        set("id", name, ob);
        if (! ob->restore())
        {
                destruct(ob);
                return "没有这个玩家。\n";
        }

        if (objectp(body = find_player(name)) && getuid(body) == name)
        {
                public_flag=query("env/public", body)?1:0;
                cname=query("name", body);
                email=query("email", body);
        } else
        {
                body = LOGIN_D->make_body(ob);
                if (! body->restore())
                {
                        destruct(ob);
                        destruct(body);
                        return "没有这个玩家。\n";
                }
                public_flag=query("env/public", body)?1:0;
                cname=query("name", body);
                email=query("email", body);
                destruct(body);
        }

        if( objectp(me) && query("id", me) == name || 
            stringp(me) && me == name)
                public_flag = 1;

        if (wiz_level(me) < 2)  // player finger
        {
                msg =  sprintf("英文代号：\t%s\n姓    名：\t%s\n权限等级：\t%s\n"
                        "电子邮件地址：\t%s\n上次连线：\t%s\n",
                        query("id", ob),
                        cname,
                        SECURITY_D->get_status(name),
                        (public_flag) ? email : "不告诉你",
                        ctime(query("last_on", ob)));

                if (objectp(body = find_player(name)) &&
                    getuid(body) == name &&
                    MESSAGE_D->visible(me, body))
                {
                        if (interactive(body))
                                msg += sprintf("\n%s目前正在连线中。\n", cname);
                        else
                                msg += sprintf("\n%s目前断线中。\n", cname);
                }
        } else          // wizard finger
        {
                msg =  sprintf("英文代号：\t%s\n姓    名：\t%s\n权限等级：\t%s\n"
                        "电子邮件地址：\t%s\n上次连线地址：\t%s( %s )\n",
                        query("id", ob),
                        cname,
                        SECURITY_D->get_status(name),
                        email,
                        query("last_from", ob),
                        ctime(query("last_on", ob)),
                );

                if (objectp(body = find_player(name)) &&
                    getuid(body) == name &&
                    MESSAGE_D->visible(me, body))
                {
                        msg += sprintf("\n%s\n", body->query_info());

                        if (interactive(body))
                        {
                                if (admin)
                                {
                                        uob = filter_array(all_interactive(),
                                                (: query_ip_number($1) == $(query_ip_number(body)) :));
                                        same = sizeof(uob);
#ifdef DB_SAVE
                                        ip_number = resolve_ip_number(query_ip_number(body));
                                        sql = sprintf("SELECT place,address FROM %s WHERE ipstart <= \"%s\" AND"
                                                      " ipend >= \"%s\" ORDER BY ipend LIMIT 1", IP_TABLE,
                                                      ip_number, ip_number);
                                        if (sizeof(ret = DATABASE_D->db_fetch_row(sql)))
                                        {
                                                where = ret[0];
                                                addr = ret[1];
                                                msg += sprintf("\n%s目前正在从 %s (%s，%s) 连线中", cname,
                                                               query_ip_number(body), where,addr);
                                        } else
#endif
                                                msg += sprintf("\n%s目前正在从 %s 连线中", cname,
                                                               query_ip_number(body));
                                        if (same > 1)
                                        {
                                                msg += sprintf("，该地址一共有 %d 位使用者。\n", same);
                                                if (previous_object() != find_object(MESSAGE_D))
                                                        // I won't return the list if this is
                                                        // called from a chat user
                                                        msg += user_list(uob, 1);
                                        } else
                                                msg += "。\n";
                                } else
                                        msg += sprintf("\n%s目前正在连线中。\n", cname);
                        } else
                                msg += sprintf("\n%s目前断线中。\n", cname);

                        if (body->name() != body->name(1))
                                msg += sprintf("该玩家目前以%s身份行动。\n", body->name());
                }
        }

        if (! objectp(body) &&
            MESSAGE_D->query_connection(name) &&
            MESSAGE_D->visible(me, name))
        {
                msg += "\n" + cname + "目前正在聊天中。\n";
        }

#ifdef DB_SAVE
        res = DATABASE_D->do_sql("select online, last_station from users where id = '" + name + "'");
        flag = arrayp(res);
        if (flag && MESSAGE_D->visible(me, name))
        {
                if ((int)res[0] == 3)
                        msg += sprintf("%s的数据目前正在漫游中。。\n", cname);
                else
                {
                        where = res[1];
                        if (stringp(where) && where != LOCAL_STATION)
                        {
                                if ((int)res[0] == 2)
                                        msg += sprintf("\n%s目前正在%s站点闭关中。\n",
                                                       cname, ! undefinedp(stations[where]) ? stations[where] : "其他",
                                                       ! undefinedp(stations[where]) ? stations[where] : "其他");
                                else
                                if ((int)res[0] == 1)
                                        msg += sprintf("\n%s目前正在%s站点连线中。\n",
                                                       cname, ! undefinedp(stations[where]) ? stations[where] : "其他",
                                                       ! undefinedp(stations[where]) ? stations[where] : "其他");
                                else
                                if ((int)res[0] == 0)
                                        msg += sprintf("\n%s目前正在%s站点，但没有连线进入游戏。\n",
                                                       cname, ! undefinedp(stations[where]) ? stations[where] : "其他",
                                                       ! undefinedp(stations[where]) ? stations[where] : "其他");
                        }
                }
        }
#endif
        destruct(ob);
        return msg;
}

string get_killer()
{
        int i;
        string msg;
        object *ob = users();

        msg = "";
        for (i = 0; i < sizeof(ob); i++)
                if ((int)ob[i]->query_condition("killer"))
                        msg += (ob[i]->short() + "\n");
        if (msg == "")
                return "本城治安良好。\n";
        else
                return "现在本城正在缉拿以下人犯：\n\n" + msg;
}

varargs string remote_finger_user(string name, int chinese_flag)
{
        object ob, body;
        string msg;
        mapping conn;
        int public_flag;
        string cname, email;

        ob = new(LOGIN_OB);
        set("id", name, ob);
        if (! ob->restore())
        {
                destruct(ob);
                return chinese_flag ? "没有这个玩家。\n" : "No such user.\n";
        }

        if (objectp(body = find_player(name)) && getuid(body) == name)
        {
                public_flag=query("env/public", body)?1:0;
                cname=query("name", body);
                email=query("email", body);
        } else
        {
                body = LOGIN_D->make_body(ob);
                if (! body->restore())
                {
                        destruct(ob);
                        destruct(body);
                        return "没有这个玩家。\n";
                }
                public_flag=query("env/public", body)?1:0;
                cname=query("name", body);
                email=query("email", body);
                destruct(body);
        }

        if (! public_flag)
                email = "不告诉你";

        if (chinese_flag)
                msg = sprintf("英文代号：\t%s\n姓    名：\t%s\n权限等级：\t%s\n"
                              "电子邮件地址：\t%s\n上次连线：\t%s\n",
                              query("id", ob),
                              SECURITY_D->get_status(name),
                              cname, email,
                              ctime(query("last_on", ob)));
        else msg =  sprintf("Name\t: %s\nStatus\t: %s\nEmail\t: %s\nLastOn\t: %s\n",
                            capitalize(query("id", ob)),
                            SECURITY_D->get_status(name),
                            email,
                            ctime(query("last_on", ob)));

        if (objectp(body = find_player(name)) &&
            !query("env/invisible", body) )
        {
                if (chinese_flag)
                        msg += "\n" + cname + "目前正在连线中。\n";
                else
                        msg += "\n" + capitalize(name) + " is currently connected.\n";
        }
        if (objectp(body = MESSAGE_D->query_connection(name)) &&
            !query("env/invisible", body) )
        {
                if (chinese_flag)
                        msg += "\n" + cname + "目前正在聊天中。\n";
                else
                        msg += "\n" + capitalize(name) + " is connected to chat now.\n";
        }

        destruct(ob);
        return msg;
}

object acquire_login_ob(string id)
{
        object ob;

        if( ob = find_player(id) ) {
                // Check if the player is linkdead
                if( query_temp("link_ob", ob) )
                        return query_temp("link_ob", ob);
        }
        ob = new(LOGIN_OB);
        set("id", id, ob);
        return ob->restore() ? ob : 0;
}
