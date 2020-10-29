// tell.c

#include <ansi.h>
#include <net/dns.h>
#include <net/messaged.h>
#include <mudlib.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

int notice_user(string my_name, string my_id, object obj, string tell_out);
int help(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string target, msg, mud;
        object obj;
        string no_tell, can_tell;
        mapping m,o;
        //string tell_out;
        m=me->query_entire_dbase();
        if(m["chblk_on"]&&!wizardp(me))
                return write(ALERT("你的频道被关闭了，在你试图发出任何信息前请先与江湖小猪联系。\n"));
        if (! arg || sscanf(arg, "%s %s", target, msg) != 2)
                return help(me);

        if (sscanf(target, "%s@%s", target, mud) == 2)
        {
                if (GTELL->send_gtell(mud, target, me, msg))
                {
                        write(MTEXT("网路讯息已送出，可能要稍候才能得到回应。\n"));
                        return 1;
                }
        }

        obj = find_player(target);
        if (! obj || ! me->visible(obj))
        {
                if (MESSAGE_D->send_msg_to(me, target, msg))
                        return 1;
                return notify_fail(ALERT("这个侠客没有登录，你无法与其交谈！\n"));
        }
        o=obj->query_entire_dbase();
        no_tell=query("env/no_tell", obj)+"";
        if (! wizardp(me) && (lower_case(no_tell) == "all" || no_tell == "全部" || is_sub(m["id"], no_tell) || is_sub(m["name"],no_tell) ))
        {
                can_tell=query("env/can_tell", obj);
                if (! is_sub(m["id"], can_tell) && ! is_sub(m["name"],can_tell))
                        return notify_fail(ALERT("对方把你列入黑名单啦，听不到你的话的。\n"));
        }
        if( o["doing"]=="neili" )
                return notify_fail(ALERT("此人正在练功。\n"));
        if ( !interactive(obj) || obj->is_net_dead()  )//要将离线攒内除外
                return notify_fail(ALERT("此人现在不在线上，听不到你的话。\n"));

        if (! living(obj))
                return notify_fail(ALERT("这人现在恐怕听不到你说的话了...\n"));

        if (me->ban_say(1))
                return 0;

        if (obj == me)
        {
                message_vision(MTEXT("$N喃喃自语。\n"), me);
                return 1;
        }

        if (! notice_user(m["name"], m["id"], obj, msg))
                return 1;

        if (query_idle(obj) >= 120)
                write(ALERT( "\n可是" + o["name"] +
                       "已经在猪圈中发呆有" + chinese_number(query_idle(obj) / 60) +
                      "分钟了，恐怕没法立刻回答你。\n"));

        return 1;
}

string remote_tell(string cname, string from, string mud, string to, string msg, int wiz_level)
{
        object ob;
        string fromid;
        string no_tell;
        string can_tell;
        string tell_out;

        if (ob = MESSAGE_D->find_user(to))
        {
                if( query("env/invisible", ob) )
                        return "这个人现在不在线上。";

                fromid = lower_case(from + "@" + mud);
                no_tell=query("env/no_tell", ob);
                if ((! intp(wiz_level) || wiz_level < 3) &&
                    (no_tell == "all" || no_tell == "ALL" ||
                     is_sub(fromid, no_tell)))
                {
                        can_tell=query("env/can_tell", ob);
                        if (! is_sub(fromid, can_tell))
                                return "这个人不想听你罗嗦啦。";
                }

                fromid = capitalize(from) + "@" + upper_case(mud);
                msg = replace_string(msg, "\n", "");
                if (cname)
                        tell_out = sprintf(HIG "%s(%s)告诉你：%s\n" NOR,
                                           cname, fromid, msg);
                else
                {
                        cname = "未知";
                        tell_out = sprintf(HIG "%s 告诉你：%s\n" NOR,
                                           fromid, msg);
                }

                to = capitalize(to);
                if (! notice_user(cname, fromid, ob, tell_out))
                        msg = sprintf(HIG "你的话没有送到%s(%s@%s)的耳边。\n" NOR,
                                      ob->name(1), to, upper_case(INTERMUD_MUD_NAME));
                else
                        msg = sprintf(HIG "你告诉%s(%s@%s)：%s" NOR, ob->name(1), to,
                                      upper_case(INTERMUD_MUD_NAME), msg);
                return msg;

        } else
                return "这个人现在不在线上。";
}

// 将消息送给对方
int notice_user(string my_name, string my_id, object obj, string tell_out)
{
        int i;
        mixed info;
        mixed *list;
        mixed piece;
//        string ico;
        object me;
        if(!objectp(me=this_player()))
                return 1;
        tell_out=replace_string(tell_out,"$","");
        tell_out=replace_string(tell_out,TMA,"");
        tell_out=replace_string(tell_out,TMB,"");
        tell_out=TMI("ctellname="+my_name+";ID="+my_id+";icon="+query("icon", me)+";"+tell_out);
        if( query("env/jam_talk", obj) )
        {
                // 阻塞式交谈
                info = ({ my_name, my_id, tell_out });
                list=query_temp("tell_list", obj);
                if (! arrayp(list) || sizeof(list) < 1)
                {
                        // 对方没有阻塞消息，直接通知对方
                        tell_object(obj, tell_out);
                        set_temp("reply", my_id, obj);
                        list = ({ info });
                } else
                if (arrayp(list[0]) && sizeof(list[0]) >= 3 &&
                    list[0][1] == my_id)
                {
                        // 对方阻塞的正是和我交谈的信息，所以
                        // 这条信息就没有必要延迟发送了
                        tell_object(obj, tell_out);
                } else
                {
                        // 遍历所有的历史信息，查看是否已经有
                        // 交谈的记录了
                        for (i = 1; i < sizeof(list); i++)
                        {
                                piece = list[i];
                                if (! arrayp(piece) || sizeof(piece) < 3 ||
                                    ! stringp(piece[2]))
                                {
                                        // 这条历史记录不合法
                                        list[i] = 0;
                                        continue;
                                }

                                if (piece[1] == my_id)
                                {
                                        // 找到了和对方以前交谈的信息
                                        if (strlen(piece[2]) > 32768)
                                        {
                                                // 历史信息已经过了32K了
                                                write(MTEXT("你已经说了好多话了，先等别人听完吧。\n"));
                                                return 0;
                                        }

                                        // 记录这次交谈的信息
                                        piece[2] += tell_out;
                                        info = 0;
                                }
                        }
                        list -= ({ 0 });

                        // 这个人还有没有听完的话呢
                        if (arrayp(info))
                        {
                                if (sizeof(list) > 12)
                                {
                                        write(MTEXT(obj->name(1) + "耳边已经有太多"
                                              "的话了，你还是等会儿再说吧。\n"));
                                        return 0;
                                }

                                // 记录这句话
                                list += ({ info });
                                if (! in_input(obj))
                                        obj->write_prompt();
                        }
                }
                set_temp("tell_list", list, obj);
        } else
        {
                // 正常聊天
                set_temp("reply", my_id, obj);
                tell_object(obj, tell_out);
        }

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：tell <某人> <讯息>

你可以用这个指令和其他地方的使用者说话。如果对方选择阻塞式交
谈，那么他可能不会立刻听到你说的话。

其他相关指令：reply、skip
HELP );
        return 1;
}