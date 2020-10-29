// agile.c 如鬼似魅

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "如鬼似魅" NOR; }

int perform(object me, string skill)
{
        mapping buff, data;
        string msg;
        int count;

        if( query("qi", me)<80 )
                return notify_fail("你的体力不支，无法竭力提升自己的速度。\n");

        msg = HIC "$N" HIC "脚尖一点，踢起一些尘"
                       "土，整个人顿时如同纸鹞一般飘飘忽忽。\n" NOR;
        count = me->query_dex()*3;

        if( BUFF_D->check_buff(me, "agile") )
                return notify_fail("你已经竭力提升你自己的速度了。\n");

        me->receive_damage("qi", 40 + random(40));
        data = ([
                "defense" : count,
        ]);
        buff = ([
                "caster" : me,
                "target" : me,
                "type"   : "agile",
                "attr"   : "bless",
                "name"   : HIC "如鬼似魅" NOR,
                "time"   : 60+random(30),
                "buff_data": data,
                "buff_msg" : msg,
                "disa_msg" : "你的如鬼似魅施展完毕，身形一顿，又慢了下来。\n",
        ]);
        BUFF_D->buffup(buff);
        return 1;
}
