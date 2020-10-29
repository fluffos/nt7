// power.c 天神降世

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "天神降世" NOR; }

int perform(object me, string skill)
{
        mapping buff, data;
        string msg;
        int count;

        if( query("qi", me)<80 )
                return notify_fail("你的体力不支，无法迅猛提升自己的战斗力。\n");

        msg = HIY "$N" HIY "双臂一伸一缩，膝部微弯，作势欲扑。\n" NOR;

        count = me->query_str();

        if( BUFF_D->check_buff(me, "spe_power") )
                return notify_fail("你已经尽力提升自己的战斗力了。\n");

        me->receive_damage("qi", 40 + random(40));
        data = ([
                "attack" : count*3,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type": "spe_power",
                "attr": "bless",
                "name": HIY "天神降世" NOR,
                "time": 60+random(30),
                "buff_data": data,
                "buff_msg": msg,
                "disa_msg" : "你施展完天神降世，松了一口气。\n",
        ]);
        BUFF_D->buffup(buff);

        return 1;
}
