#include <ansi.h>

inherit F_CLEAN_UP;

int help();

int main(object me,string arg)
{
        string cmd,*res;
        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;
        if(!arg)
                return help();
        if(sscanf(arg,"%s %s",cmd,arg)!=2)
        {
                write("参数错误！\n");
                return help();
        }
        
        cmd=lower_case(cmd);
        if(cmd!="select")
                return notify_fail("暂时不能执行除了select以外的SQL查询！\n");
        log_file("sqlcmd","\n"+ctime(time())+me->name()+"("+query("id", me)+")执行了SQL查询：\n"+cmd+""+arg);
        res=DATABASE_D->do_sql(cmd+" "+arg);
        if(arrayp(res)&&sizeof(res))
                write("SQL查询返回结果：\n"+save_variable(res)+"\n");
        else
                write("SQL查询无返回结果！\n");
        return 1;
}

int help()
{
        write(NOR+"\nSQL查询命令测试版！Written By JackyBoy\n\n"+
                "命令语法："+HIG+"sql <SQL语句> \n"+NOR
                "目前只支持"+HIR+"select"+NOR+"查询！\n");
        return 1;
}