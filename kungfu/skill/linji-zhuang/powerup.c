// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;
        int di;
        object weapon;

        if( target != me )
                return notify_fail("你只能用临济庄提升自己的战斗力。\n");

        if( (int)query("neili", me) < 100 )
                return notify_fail("你的内力不够。\n");

        if( BUFF_D->check_buff(me, "powerup") ) 
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        if( query("sex", me) ) di = 0; else di = skill * 2;
        if( di > 10000 ) di = 10000;

        msg = MAG "$N" MAG "微一凝神，运起临济庄，一声娇喝，"
                        "四周的空气仿佛都凝固了！\n" NOR;

        if( objectp(weapon = query_temp("weapon", me)) )
        {
                if (di >= 95)
                        message_combatd(HIR "$N" HIR "脸色一沉，运起临济庄神通，霎时间" +
                                        weapon->name() + HIR "光华四射，漫起无边杀意。\n" NOR, me);
                else
                if (di >= 80)
                        message_combatd(HIR "$N" HIR "潜运内力，只见" +
                                        weapon->name() + HIR "闪过一道光华，气势摄人，令人肃穆。\n" NOR, me);
                else
                if (di >= 30)
                        message_combatd(HIR "$N" HIR "默运内力，就见那" +
                                        weapon->name() + HIR "隐隐透出一股光芒，闪烁不定。\n" NOR, me);
        }
        
        data = ([
                "attack" : skill/3,
                "defense": skill/3,
                "damage" : di,
                "unarmed_damage": di,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "临济十二庄·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的临济十二庄运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}
