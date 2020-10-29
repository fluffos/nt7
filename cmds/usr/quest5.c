#include <ansi.h>
inherit F_CLEAN_UP;
int time_period(int timep, object me);
int main(object me, string arg)
{
        int mark;
        int quest;
        string *site;

        site=({"玄武门内","青龙门内","朱雀门内","白虎门内"});
        if( !(quest=query("jungong", me)) )
        return notify_fail(
               HIW"你并没有做过任何郭靖任务，想试一下吗？\n"NOR);

        mark=query_temp("guo_shoucheng/mark_shadi", me);

        if( mark && mark < 5 )
             write(HIW"\n你现在的任务是去协助"HIR+site[mark-1]
                     +HIW"的宋军，抗击蒙古鞑子的入侵！\n"NOR);
         
        else
          if( query_temp("guo_shoucheng/mark_jianlou", me) )
             write(HIW"\n你现在的任务是去协助青龙门内"HIR"东城箭楼"
                    +HIW"的宋军，担任狙击蒙古弓箭手的任务！\n"NOR);
        else
             write(
HIW"\n===============================================================\n"NOR
+HIR"            你已经荣立军功"HIY
+chinese_number(quest)+HIR"策！\n"NOR+
HIW"===============================================================\n"NOR);

       return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : quest5  这个指令可以显示出你已经参与郭靖任务情况。
HELP
        );
        return 1;
}
