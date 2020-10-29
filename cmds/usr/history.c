// This program is a part of NT mudlib

#include <ansi.h>
#include <mudlib.h>
inherit F_CLEAN_UP; 

#define HCMD            0
#define HTIME           1

#define DEFAULT_SIZE    25

string help = @HELP
指令历程

这个指令用来检视您曾使用过的指令纪录，您可以透过下列指令来使用您的指令纪录

!!              重复上一个指令
!<指令编号>     重复 <指令编号> 的指令

指令格式:
history <指令数>                显示最近 <指令数> 笔的指令历程
history <使用者代号>            显示 <使用者> 的指令历程 (巫师专用)
history <指令数> <使用者代号>   显示 <使用者> 最近 <指令数> 笔的指令历程 (巫师专用)
history <使用者代号> <指令数>   同上

history game                    显示游戏的重大历史事件

相关指令: 
HELP;

int main(object me, string arg)
{
        int i, ttl_size, size, start;
        string msg;
        string *cmd_history;
        object ob;

        if( !wizardp(me) && time()-query_temp("last_history", me)<3 ) 
        { 
                write("系统气喘嘘地叹道：慢慢来 ....\n");   
                return 1; 
        } 

        if( arg == "game" )
        {
                string *game_history = HISTORY_D->query_history();        
                
                msg = MUD_FULL_NAME"重大历史事件\n";
                msg += WHT"——————————————————————————————————————————————\n"NOR;
                msg += HIC"编号 时间              ID        事件\n"NOR;
                msg += WHT"——————————————————————————————————————————————\n"NOR;
                
                for(i=0;i<sizeof(game_history);i+=4)
                {
                        msg +=sprintf(HIW"%-5d"NOR CYN"%-18s"NOR YEL"%-10s"NOR HIC"%s\n"NOR, i/4+1, TIME_D->replace_ctime(game_history[i]), game_history[i+2],game_history[i+3]);
                }
                
                msg += WHT"——————————————————————————————————————————————\n"NOR;
                me->start_more(msg);
                return 1;
        }
        
        if( wizardp(me) && arg == "-l" )
        {
                object *sortusers;
                
                msg = "排名 玩家名称                   指令数   速度(每秒)   五百平均 系统负荷\n";
                msg += WHT"———————————————————————————————————————\n"NOR;
                sortusers = filter_array(users(), (: playerp($1) :));
                sortusers = sort_array(sortusers, (: to_float($1->total_command_count())/(time() - query_temp("logon_time", $1)) < to_float($2->total_command_count())/(time() - query_temp("logon_time", $2)) ? 1 : -1 :));


                foreach(ob in sortusers)
                {
                        cmd_history = ob->query_history();
                        
                        msg += sprintf("%-3d. %-27s%-9d%-13.2f%-8.2f %-8s %s\n", 
                                ++i, 
                                ob->query_idname(), 
                                ob->total_command_count(), 
                                to_float(ob->total_command_count())/(time() - query_temp("logon_time", ob)),
                                sizeof(cmd_history) ? to_float(sizeof(cmd_history))/((cmd_history[<1][1] - cmd_history[0][1])||1) : 0.,
                                count(ob->query_total_timecost(), "/", ob->total_command_count()||1),
                                query("cmdlimit", ob) ? HIR"(Limited)"NOR:"",
                        );

                }
                msg += WHT"———————————————————————————————————————\n"NOR;
                me->start_more(msg);
                return 1;
        }
        if( !arg || !wizardp(me) ) ob = me;
        else if( sscanf(arg, "%d %s", size, arg) == 2 ) ob = find_player(arg);
        else if( sscanf(arg, "%s %d", arg, size) == 2 ) ob = find_player(arg);
        else if( sscanf(arg, "%d", size) == 1 ) ob = me;
        else ob = find_player(arg);

        if( !objectp(ob) )
                return tell(me, "没有 " + arg + " 这位玩家。\n");

        if( ob != me && wiz_level(me->query_id(1)) < wiz_level(ob->query_id(1)) )
                return tell(me, pnoun(2, me) + "没有权限查阅" + ob->query_idname() + "的历史指令纪录。\n");

        cmd_history = ob->query_history();

        if( !(ttl_size = sizeof(cmd_history)) )
                return tell(me, (me==ob ? pnoun(2, me):ob->query_idname()) + "没有任何历史指令纪录。\n");

        if( size <= 0 ) size = DEFAULT_SIZE;
        if( size > ttl_size ) size = ttl_size;
        
        msg = (me==ob ? pnoun(2, me):ob->query_idname())+"总共有 "+ttl_size+" 笔指纪录，指令平均速度 "+(ob->total_command_count() > 0 ? sprintf("%.2f", to_float(ob->total_command_count())/((time() - query_temp("logon_time", ob))||1)) : 0)+" (指令数/秒)，下列为最近的 "+size+" 笔: \n"; 


        start = ttl_size - size;

        i = ob->total_command_count() - size;
        foreach(int *cmd in cmd_history[start..])
                msg += sprintf(HIW" [%4d]"NOR + WHT" %s"NOR" %s\n"NOR, (++i), ctime(cmd[HTIME])[11..18], cmd[HCMD]);

        me->start_more(msg);
        return 1;
}

int help(object me) 
{
        write(help);
        return 1;
}
