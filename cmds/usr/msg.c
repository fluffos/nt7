// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <command.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string *data;
        string type, id;
        object  target;
        int     i, t, total, size;

        seteuid(ROOT_UID);

        MYGIFT_D->check_mygift(me, "newbie_mygift/msg");

        if( arg == "clear" ) {
                me->clear_msg_log();
                write("清除掉所有的讯息纪录。\n");
                me->save();
                return 1;
        }

        if( arg == "system" ) {
                t=query("msg/time", me);
                if( !t ) {
                        tell_object(me, WHT "欢迎您进入" + LOCAL_MUD_NAME() +
                                        WHT "，今后请使用" HIY " msg " NOR WHT
                                        "命令查阅邮件信息。\n" NOR);
                        set("msg/time", time(), me);
                        return 1;
                }
                data = me->query_mail();
                if( !arrayp(data) || !sizeof(data) ) {
                        tell_object(me, HIY "您没有收到新邮件。\n" NOR);
                        return 1;
                }

                size = sizeof(data);
                total = 0;
                for( i=size-1;i>=0;i-=3 ){
                        if( to_int(data[i-2]) > t )
                                total++;
                        else
                                break;
                }
                if( !total )
                        tell_object(me, HIY "你目前没有未曾阅读过的邮件。\n" NOR);
                else
                        tell_object(me, sprintf(WHT "你目前一共有 " HIY "%d" NOR
                                        WHT " 条邮件还没有阅读，请使用("
                                        HIY "msg" NOR WHT ")命令阅读。\n" NOR, total));
                return 1;
        }
        if( arg == "info" ) {
                mapping setup=query("msg", me);

                if( !mapp(setup) || !sizeof(keys(setup)-({ "size" })) )
                        return notify_fail("没有设定纪录任何讯息。\n");

                map_delete(setup, "size");
                write("目前设定的讯息纪录项目："+implode(keys(setup), ", ")+"\n");
                return 1;
        }

        if( arg && (size = to_int(arg)) ) {
                if( size < 10 || size > 1000 )
                        return notify_fail("讯息最少纪录 10 笔，最多纪录 1000 笔。\n");

                set("msg/size", size, me);
                write("设定讯息纪录笔数为 "+size+" 笔。\n");
                me->save();
                return 1;
        }

        if( arg && sscanf(arg, "mail %s", id) == 1 ) {
                if( !wizardp(me) && time()-query_temp("last_mail_msg", me)<60 )
                        return notify_fail(HIC "你在一分钟内只能发送一条短消息。\n" NOR);

                if( id == query("id", me) )
                        return notify_fail(HIC "你有没有问题，自己给自己写信息？！\n" NOR);

                target = UPDATE_D->global_find_player(id);

                if( !objectp(target) )
                        return notify_fail("没有这个玩家。\n");

                UPDATE_D->global_destruct_player(target, 1);

                /*
                if( !wizardp(me)
                     && !MEMBER_D->is_valid_member(query("id", me) )
                    && id != "lonely" )
                          return notify_fail("只有会员才能发送短消息。\n");
                */

                set_temp("last_send_msg", time(), me);
                write(HIG "请输入短消息内容（长度不超过500个汉字）。\n" NOR);

                me->edit(bind((: call_other, __FILE__, "done", me, id :), me));

                return 1;
        }
        else if( arg && sscanf(arg, "+%s", type) == 1 ) {
                if( type == "say" || type == "tell" || type == "emotion" || type == "reply" || type == "answer" || type == "whisper" || CHANNEL_D->valid_channel(wiz_level(me->query_id(1)), type) ) {
                        set("msg/"+type, 1, me);
                        write("开始纪录 "+type+" 的讯息。\n");
                        me->save();
                        return 1;
                }
                else
                        return notify_fail("无法设定 "+type+" 这种讯息。\n");
        }
        else if( arg && sscanf(arg, "-%s", type) == 1 ) {

                if( type == "say" || type == "tell" || type == "emotion" || type == "reply" || type == "answer" || type == "whisper" || CHANNEL_D->valid_channel(wiz_level(me->query_id(1)), type) )
                {
                        delete("msg/"+type, me);
                        write("停止纪录 "+type+" 的讯息。\n");
                        me->save();
                        return 1;
                }
                else
                        return notify_fail("无法设定 "+type+" 这种讯息。\n");
        }

        if( wizardp(me) && arg && objectp(target = find_player(arg)) && wiz_level(target) <= wiz_level(me) )
                data = target->query_msg_log();
        else
                data = me->query_msg_log();

        size = sizeof(data);

        if( size ) {
                string *str;

                str = ({ (target?target->query_idname():"")+"共有 "+(size/3)+" 笔旧讯息纪录：\n--------------------------------------------------------------------------\n" });

                if( arg && !target ) {
                        for(i=0;i<size;i+=3)
                                if( data[i+1] == arg )
                                        if( arg != "mail" )
                                        str += ({ HIW+ctime(atoi(data[i]))[11..15]+NOR"-"+data[i+2] });
                                        //str += ({ HIW+TIME_D->replace_ctime(atoi(data[i]))+NOR"-"+data[i+2] });
                                        else
                                        str += ({ HIW+ctime(atoi(data[i]))[11..]+NOR"-"+data[i+2] });
                }
                else {
                        for(i=0;i<size;i+=3)
                                   str += ({ HIW+ctime(atoi(data[i]))[11..15]+NOR"-"+data[i+2] });
                                //str += ({ HIW+TIME_D->replace_ctime(atoi(data[i]))+NOR"-"+data[i+2] });
                }

                str += ({ "--------------------------------------------------------目前时刻 "HIW+ctime(time())[11..15]+NOR"----\n" });
                me->start_more(implode(str, ""));
                set("msg/time", time(), me);
                me->save();
        }
        else
                write(target?target->query_idname():""+"目前没有任何讯息纪录。\n");

        return 1;
}

void done(object me, string id, string msg)
{
        object ob;
        // string mail, *mail_log;

        if( !me || !msg || msg == "" )
                return;

        // 检查长度
        if( sizeof(msg) > 1000 ) {
                write("短消息过长，最长不能大于1000个字节。\n");
                return;
        }

        msg = replace_string(msg, "\"", "");
        if( objectp(ob = find_player(id)) ) {
                if( !wizardp(me) && ob->is_mail_limit() ) {
                        tell_object(me, ob->query_idname() + "的短消息已满！\n");
                        UPDATE_D->global_destruct_player(ob, 1);
                        return;
                }

                ob->add_msg_log("mail", HIR "【邮件信息】来自" + me->query_idname() + HIR "的邮件内容如下\n"HIW+msg+NOR"\n");
                ob->save();
                tell_object(ob, HIR "【邮件信息】你新收到一封来自" + me->query_idname() + HIR "的邮件(msg mail)。\n" NOR);
        } else {
#ifdef DB_SAVE
                mail = DATABASE_D->db_query_player(id, "f_mail");
                mail_log = restore_variable(mail);
                if( !arrayp(mail_log) ) mail_log = ({});

                if( wiz_level(id) < 1 ) {
                        if( !wizardp(me) && sizeof(mail_log) >= 60 ) {
                                tell_object(me, "对方的短消息已满！\n");
                                return;
                        }
                } else {
                        if( sizeof(mail_log) >= 300 ) {
                                tell_object(me, "对方的短消息已满！\n");
                                return;
                        }
                }
                msg = HIR "【邮件信息】来自" + me->query_idname() + HIR "的邮件内容如下\n"HIW+msg+NOR"\n";
                mail_log += ({ time(), "mail", msg });

                mail = save_variable(mail_log);
                DATABASE_D->db_set_player(id, "f_mail", mail);
#else
                ob = UPDATE_D->global_find_player(id);
                if( ob->is_mail_limit() ) {
                        tell_object(me, ob->query_idname() + "的短消息已满！\n");
                        UPDATE_D->global_destruct_player(ob, 1);
                        return;
                }

                ob->add_msg_log("mail", HIR "【邮件信息】来自" + me->query_idname() + HIR "的邮件内容如下\n"HIW+msg+NOR"\n");
                ob->save();
                UPDATE_D->global_destruct_player(ob, 1);
#endif
        }

        tell_object(me, HIY "【邮件信息】你的短消息已经成功发送！\n" NOR);
        return;
}

int help(object me)
{
        write(@HELP
显示最近收到的 1000 个聊天/谣言频道或是密语讯息。

msg                     查看所有讯息的纪录
msg 种类                查看某类讯息的纪录，例如 msg mail 则仅查看 mail 信息
msg +种类               增加某类讯息的纪录
msg -种类               停止某类讯息的纪录
msg 笔数                设定讯息纪录笔数，最少纪录 10 笔，最多纪录 1000 笔
msg clear               删除所有讯息
msg info                查询目前的讯息纪录项目
msg mail <某人>         给某人(不在线上)留言

讯息种类包括：公开频道(chat, rumor, ...), say, tell, ...

HELP );
        return 1;
}
