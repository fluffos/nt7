// snowyu piaomiao

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me);
void checking(object me);

string name() { return "云烟飘渺"; }

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        int lvl, att, dam;

        lvl = (int)me->query_skill("wuluo-zhang", 1);
        att = lvl/4+ random(lvl/2);
        dam = lvl/2 + random(lvl/2);

        if( !target ) target = offensive_target(me);

        if( query("family/family_name", me) != "段氏皇族" && !wizardp(me) )
                return notify_fail(HIW "你非大理弟子无法施展「云烟飘渺」！\n" NOR);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail(HIW "云烟飘渺只能对战斗中的对手使用。\n");

        if( me->query_skill("force") < 200 )
                return notify_fail(HIW "你的内功火候未到！\n");

        if( me->query_skill("wuluo-zhang", 1) < 150 )
                return notify_fail(HIW "你的基本五罗轻烟掌尚未纯熟，无法施展云烟飘渺！\n");

        if( me->query_skill("strike", 1) < 150 )
                return notify_fail(HIW "你的基本掌法尚未纯熟，无法施展云烟飘渺！\n");

        if( me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail(HIW "你所用的内功心法不是枯荣禅功，无法聚集真气。\n");

        if( query("max_neili", me) <= 2000 )
                return notify_fail(HIW "你的内力修为不足，无发体会出云烟飘渺！\n" NOR);

        if( query("neili", me)<800 )
                return notify_fail(HIW "你的内力不够，内劲不足以施展云烟飘渺！\n" NOR);

        if( BUFF_D->check_buff(me, "wlz_piaomiao") )
                return notify_fail(HIW "你正在使用云烟飘渺！\n");

        msg = HIB"$N运起内功心法，将真气凝聚运往手掌，顿时$N手掌反白，掌中泛起一阵"NOR HIW"白烟"NOR HIB"。\n" NOR;

        addn("neili", -200, me);
        
        data = ([
                "attack": att,
                "unarmed_damage": dam,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "wlz_piaomiao",
                "attr"  : "bless",
                "name"  : "五罗轻烟掌·云烟飘渺",
                "time"  : lvl/10,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你收起了聚起的内劲，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        
        COMBAT_D->do_attack(me, target, query_temp("weapon", me));

        call_out("checking", 1, me);
        return 1;
}

void checking(object me)
{
        if( !living(me) || me->is_ghost()  )
        {
                remove_effect(me);
                return;
        }

        if( !me->is_fighting() )
        {
                remove_effect(me);
                tell_object(me, MAG "\n你将气息调节至原本的状态。\n\n"NOR);

                return;
        }
        
        remove_call_out("checking");
        call_out("checking", 1, me);
        return;
}

void remove_effect(object me)
{
        if( !me ) return;
        
        BUFF_D->debuff(me, "wlz_piaomiao", 1);
}
