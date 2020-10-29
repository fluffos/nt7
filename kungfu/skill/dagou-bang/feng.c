// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "封字诀" NOR; }

int perform(object me, object target)
{
        object weapon;
        string wp;
        int skill;
        int fmsk = me->query_skill("bixue-danxin", 1);
        mapping buff, data;
        string msg;

        if (! target) target = offensive_target(me);

        if( BUFF_D->check_buff(me, "parryup") )
                return notify_fail("你现在正在施展" + name() + "。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        skill = me->query_skill("dagou-bang", 1);

        if (skill < 120)
                return notify_fail("你打狗棒法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("你没有激发打狗棒法，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的内功火候不足，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        wp = weapon->name();

        msg = HIG "$N" HIG "使出打狗棒法「" HIY "封"
                        HIG "」字诀，手中" + wp + HIG "疾速舞"
                        "动，幻出许许棒影护住周身。\n" NOR;

        addn("neili", -150, me);
        me->receive_damage("qi", 0);
        
        data = ([
                "defense": skill / 3 + fmsk / 5,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "parryup",
                "attr"  : "bless",
                "name"  : "打狗棒法·封字诀",
                "time"  : skill/2,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的封字诀施展完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}