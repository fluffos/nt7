// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "圆满势" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        mapping buff, data;
        string msg;
        object weapon;
        string wp;
        int skill;

        if( BUFF_D->check_buff(me, "ryl_yuan") )
                return notify_fail("你现在正在施展" + name() + "。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "hammer" )
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("hammer") != "riyue-lun")
                return notify_fail("你没有激发日月轮法，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("你没有激发龙象般若功，难以施展" + name() + "。\n");

        if ((int)me->query_skill("riyue-lun", 1) < 120)
                return notify_fail("你的日月轮法火候不足，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的内功火候不足，难以施展" + name() + "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        wp = weapon->name();

        msg = HIY "$N" HIY "吐气扬声，施出日月轮法「" HIW "圆满势"
                        HIY "」，手中" + wp + HIY "运转如飞，迅速护住周身要"
                        "害。\n" NOR;

        skill = me->query_skill("riyue-lun", 1);

        addn("neili", -200, me);
        data = ([
                "defense": skill/2,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "ryl_yuan",
                "attr"  : "bless",
                "name"  : "日月轮法·圆满势",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的圆满势运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if (me->is_fighting())
                me->start_busy(2);

        return 1;
}
