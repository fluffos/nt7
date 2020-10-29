// This program is a part of NT MudLIB

#include <ansi.h>

inherit F_CLEAN_UP;

#define DATA_PATH      "/data/bug/"
#define BUG_D   "/adm/daemons/bugd"
#define PER_REPORT_TIME_LIMIT   60

#define LIST_OPT_ALL    (1<<0)

string help = @HELP

bug -a                          新增 bug 回报
bug -l                          列出 bug 资料
bug <编号>                      读取 bug 详细内容
bug -r <编号>                   回应 bug 处理情形       巫师专用
bug -d <编号>[.<回复编号>]      删除 bug 某篇或某篇回复 巫师专用
bug                             读取错误回溯            巫师专用
bug [ID]                        读取某人的错误回溯      巫师专用

HELP;

string big_number_check(mixed bn)
{
        int negtive;

        if( !bn ) return 0;

        if( intp(bn) )
                return bn+"";
        else if( !stringp(bn) )
                return 0;

        if( bn[0] == '-' )
        {
                bn = bn[1..];
                negtive = 1;
        }

        bn = replace_string(bn, ",", "");

/*
        if( bn[<1] == 'k' || bn[<1] == 'K' )
                bn = bn[0..<2]+"000";
        else if( bn[<1] == 'm' || bn[<1] == 'M' )
                bn = bn[0..<2]+"000000";
        else if( bn[<1] == 'g' || bn[<1] == 'G' )
                bn = bn[0..<2]+"000000000";
*/
        while(bn[0]=='0') bn = bn[1..];

        foreach(int i in bn)
                if( i < '0' || i > '9' )
                        return 0;

        if( bn == "" )
                return 0;
        else
                return negtive ? "-"+bn : bn;
}

void edit_bug_content(object me, string title, string content)
{
        string number;

        if( time()-query_temp("bug_report", me)<PER_REPORT_TIME_LIMIT )
                return tell_object(me, "你必须再隔 "+(PER_REPORT_TIME_LIMIT + query_temp("bug_report", me) - time())+" 秒后才能再回报一次 Bug。\n"NOR);

        number = BUG_D->add_bug(me, title, content);

        tell_object(me, HIY"感谢你的 Bug 回报使得这个世界更加完美。\n"NOR);
        tell_object(me, HIY"\n已将你所回报的 Bug 存入资料库中，编号为 "+number+"，请利用 bug -l 随时注意处理状况。\n"NOR);

        set_temp("bug_report", time(), me);

        me->finish_input();
}

void input_bug_title(object me, string title)
{
        if( !title || !title[0] )
        {
                tell_object(me, "取消 Bug 回报输入。\n");
                return me->finish_input();
        }

        if( strlen(filter_color(title,1)) > 30 )
        {
                tell_object(me, "回报主题不得超过 30 个字元。\n");
                return me->finish_input();
        }

        if( query_temp("big5", me) )
                title = LANGUAGE_D->Big52GB(title);

        tell_object(me, "你所输入的 Bug 回报主题为：“"+title+NOR+"”\n");
        tell_object(me, HIY"请输入欲回报的 Bug 详细内容。\n"NOR);
        me->edit( (: edit_bug_content, me, title :) );
}

void edit_reply_content(object me, string number, string status, string content)
{
        BUG_D->reply_bug(me, number, status, content);

        tell_object(me, "回应编号第 "+number+" 号 Bug 完毕。\n");

        me->finish_input();
}

void confirm_input_reply(object me, string number, string status, string confirm)
{
        if( stringp(confirm) )
                confirm = lower_case(confirm);

        switch(confirm)
        {
                case "yes":
                case "y":
                        tell_object(me, HIY"请输入处理详细内容。\n"NOR);
                        me->edit( (: edit_reply_content, me, number, status :) );
                        return;
                default:
                        tell_object(me, HIY"不输入处理详细内容。\n"NOR);
                        BUG_D->reply_bug(me, number, status);
                        me->finish_input();
                        break;
        }
}


void input_reply_status(object me, string number, string arg)
{
        string status;

        switch(arg)
        {
                case "1":       status = HIR"未处理"NOR;        break;
                case "2":       status = HIY"处理中"NOR;        break;
                case "3":       status = HIC"已修复"NOR;        break;
                case "4":       status = HIR"无法修复"NOR;      break;
                case "5":       status = HIW"不需处理"NOR;      break;
                case "6":       status = HIM"需再回报"NOR;      break;
                default:        status = HIR"未处理"NOR;        break;
        }

        tell_object(me, "是否输入处理详细内容？(Yes/No):");
        input_to( (: confirm_input_reply, me, number, status :) );
}

int main(object me, string arg)
{
        object ob;
        string number;
        mapping data;

        MYGIFT_D->check_mygift(me, "newbie_mygift/bug");
        if( wizardp(me) )
        {
                if( !arg || !arg[0] )
                {
                        if( !query_temp("bug_msg", me) )
                                return notify_fail("你身上没有错误回溯资料。\n");

                        me->start_more(query_temp("bug_msg", me));
                        return 1;
                }
                else if( ob = find_player(arg) )
                {
                        if( !query_temp("bug_msg", ob) )
                                return notify_fail(ob->query_idname()+"身上没有错误回溯资料。\n");
                        me->start_more(query_temp("bug_msg", ob));
                        return 1;
                }
                else if( sscanf(arg, "-r %s", number) )
                {
                        if( !BUG_D->bug_exists(number) )
                                return notify_fail("并没有编号 "+number+" 的 Bug 存在。\n"NOR);

                        data = restore_variable(read_file(DATA_PATH+number)); 
                        tell_object(me, HIY"请输入目前处理状况编号：\n[1]"HIR"未处理"NOR" [2]"HIY"处理中"NOR" [3]"HIC"已修复"NOR" [4]"HIR"无法修复"NOR" [5]"HIW"不需处理"NOR" [6]"HIM"需再回报"NOR"\n");
                        tell_object(me, CYN+"\n"+data["content"]+"\n"+NOR+":"); 
                        input_to( (: input_reply_status, me, number :) );
                        return 1;
                }
                else if( sscanf(arg, "-d %s", number) )
                {
                        int reply;

                        sscanf(number, "%s.%d", number, reply);

                        if( !BUG_D->bug_exists(number) )
                                return notify_fail("并没有编号 "+number+" 的 Bug 存在。\n"NOR);

                        if( reply > 0 )
                        {
                                BUG_D->remove_bug(me, number, reply);
                                tell_object(me, "删除编号第 "+number+" 号 Bug 的第 "+reply+" 篇回应。\n"NOR);
                        }
                        else
                        {
                                BUG_D->remove_bug(me, number);
                                tell_object(me, "删除编号第 "+number+" 号 Bug 的所有资料。\n"NOR);
                        }

                        return 1;
                }
        }

        if( !arg )
                return notify_fail(help);

        else if( arg == "-l" )
        {
                me->start_more(BUG_D->list_bug(1));
                return 1;
        }
        else if( arg == "-a" )
        {
                tell_object(me, HIW"欢迎使用"WHT"臭虫(Bug)回报系统\n"NOR HIG"回报 Bug 时请详述发生时间、所在的位置、下达过的指令与系统显示的讯息\n详细的资料将可以帮助巫师快速解决你遇到的 Bug。\n"NOR);
                tell_object(me, HIY"请输入欲回报的 Bug 主题(仅主题，非详细内容)，或直接按 Enter 取消输入。\n:"NOR);
                input_to( (: input_bug_title, me :) );
                return 1;
        }
        else if( big_number_check(arg) )
        {
                if( !BUG_D->bug_exists(arg) )
                        return notify_fail("并没有编号 "+arg+" 的 Bug 存在。\n"NOR);

                tell_object(me, BUG_D->query_bug(arg));
                return 1;
        }
        else return notify_fail(help);
}

int help(object me)
{
        write(help);
        MYGIFT_D->check_mygift(me, "newbie_mygift/bug");
        return 1;
}
