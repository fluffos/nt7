// block.c
// By Find.

#include <ansi.h>

string head="\t---- "+"用户账号管理器"+" ----";

nomask int main(object me, string arg)
{
        string wiz_status;

        if (me != this_player(1)) 
                return 0;
        
        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return notify_fail("只有(arch)以上的巫师才能执行对用户账号的管理\n");
                
        seteuid(ROOT_UID);

        write("\n" + head + "\n\n\n\t1> 封锁一个用户账号。");
        write("\n\n\t2> 将一个已封锁的用户账号解封。");
        write("\n\n\t3> 查询一个用户账号是否被封锁。");
        write("\n\n\t4> 列出所有被封锁的用户账号。\n\n\n");

        write("选择数字(1-4)，[return] 返回上级，q 退出>");
        input_to("do_select", 0, me);
        return 1;
}

protected void do_select(string arg,object me)
{
        int s;
        string promot;

        if( arg == "" || arg == "q" )
        {
                write("ok.\n");
                return;
        }

        s = to_int(atoi(arg));
        if( (s<1) || (s>4) )
        {
                printf(CUP(2));
                write(HIY"<可选择的数字范围(1-4)>                                \n"NOR);
                write("选择数字(1-4)，[return] 返回上级，q 退出>");
                input_to("do_select",0,me);
                return;
        }

        switch (s)
        {
                case 1:
                        promot = "请输入你要封锁的用户账号：";
                        break;
                case 2:
                        promot = "请输入你要解封的用户账号：";
                        break;
                case 3:
                        promot = "请输入你要查询的用户账号：";
                        break;
                case 4:
                        me->start_more(AHACK_D->blocked_list());
                        write("\n[按任意键继续]\n");
                        input_to("break_point",0,me);
                        return;
                default:
                        return;
        }

        printf(CUP(1)+DELLINE);
        write(promot);
        input_to("do_process",0,s,me);
        return;
}

protected void do_process(string arg,int s,object me)
{
        if( (s<1) || (s>3) )
        {
                write("执行项目错误。\n");
                return;
        }

        if(arg == "")
        {
                write("\n"+head+"\n\n\n\t1> 封锁一个用户账号。");
                write("\n\n\t2> 将一个已封锁的用户账号解封。");
                write("\n\n\t3> 查询一个用户账号是否被封锁。");
                write("\n\n\t4> 列出所有被封锁的用户账号。\n\n\n");
                write("选择数字1-4，[return] 返回上级，q 退出>");
                input_to("do_select",0,me);
                return;
        }

        if(arg == "q")
        {
                write("ok.\n");
                return;
        }

        switch (s)
        {
                case 1:
                        printf(CUP(2));
                        if(wiz_level(me) < wiz_level(arg))
                                write(HIR"<你没有权力封锁一个巫师级别比你高的账号。>\n"NOR);
                        else if(AHACK_D->block_account(arg))
                        {
                                write(HIG"<账号 "+arg+" 已经被成功封锁。>\n"NOR);
                                log_file("block",sprintf("%s(%s) 将账号 %s >>>封锁，时间 %s。\n",
                                        query("name", me),query("id", me),arg,ctime(time())));
                        }
                        else
                                write(HIY"<账号 "+arg+" 已在封锁列表，不能再次封锁。>\n"NOR);
                        write("选择数字1-4，[return] 返回上级，q 退出>");
                        input_to("do_select",0,me);
                        return;

                case 2:
                        printf(CUP(2));
                        if(AHACK_D->unblock_account(arg))
                        {
                                write(HIG"<账号 "+arg+" 已经被成功被解封。>\n"NOR);
                                log_file("block",sprintf("%s(%s) 将账号 %s 解封，时间 %s。\n",
                                        query("name", me),query("id", me),arg,ctime(time())));
                        }
                        else
                                write(HIY"<账号 "+arg+" 没有被封锁，无法解封。>\n"NOR);
                        write("选择数字1-4，[return] 返回上级，q 退出>");
                        input_to("do_select",0,me);
                        return;
                case 3:
                        printf(CUP(2));
                        if(AHACK_D->query_block(arg))
                                write(HIY"<账号 "+arg+" 目前处于被封锁状态。>\n"NOR);
                        else
                                write(HIY"<账号 "+arg+" 没有被封锁。>\n"NOR);
                        write("选择数字1-4，[return] 返回上级，q 退出>");
                        input_to("do_select",0,me);
                        return;
                default:
                        return;
        }
}

protected void break_point(string arg,object me)
{
        write("\n"+head+"\n\n\n\t1> 封锁一个用户账号。");
        write("\n\n\t2> 将一个已封锁的用户账号解封。");
        write("\n\n\t3> 查询一个用户账号是否被封锁。");
        write("\n\n\t4> 列出所有被封锁的用户账号。\n\n\n");

        write("选择数字1-4，[return] 返回上级，q 退出>");
        input_to("do_select",0,me);
        return;
}


int help(object me)
{
        write(@HELP
指令格式 : block

对账户的禁止登陆的管理。

HELP
    );
    return 1;
}