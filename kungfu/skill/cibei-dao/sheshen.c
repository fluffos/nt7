// This program is a part of NITAN MudLIB
// sheshen.c 「舍身喂鹰」

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return "舍身喂鹰"; }

int perform(object me)
{
        object weapon;
        int skill;
        string msg;
        mapping buff, data;

        if ((int)me->query_skill("cibei-dao", 1) < 60)
                return notify_fail("你的慈悲刀法不够娴熟，不会使用「舍身喂鹰」。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，无法使用「舍身喂鹰」。\n");

        if( BUFF_D->check_buff(me, "atkup") )
                return notify_fail("你已经在运功中了。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        skill = me->query_skill("cibei-dao", 1);
        msg = HIR "$N" HIR "使出慈悲刀法「舍身喂鹰」，将浑身的功力都运到" +
              weapon->name() + HIR "上！\n" NOR;

        data = ([
                "attack" : skill/3,
                "defense": -skill/5,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "atkup",
                "attr"  : "bless",
                "name"  : "慈悲刀法·舍身喂鹰",
                "time"  : skill/4,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的舍身喂鹰运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}
