// This program is a part of NITAN MudLIB
// zhu.c 九羽天诛

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "九羽天诛"; }

int perform(object me, object target)
{
        int bonus, hits;
        object weapon;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「九羽天诛」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
              || query("skill_type", weapon) != "sword" )
                return notify_fail("你需要一把剑才能施展「九羽天诛」。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的内力所剩无几，无法施展「九羽天诛」。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不足，无法施展「九羽天诛」。\n");

        if ( me->query_skill("tianyu-qijian", 1) < 100 )
                return notify_fail("你的天羽奇剑不够娴熟，不能使用「九羽天诛」。\n");

        if ( me->query_skill("sword", 1) < 100 )
                return notify_fail("你的基本剑法不够娴熟，不能使用「九羽天诛」。\n");

        if( query("jiali", me)<1 )
                return notify_fail("你加力太少，无法使用「九羽天诛」。\n");

        if( query("09g/ring", me) == "li" )
        {
                if ( me->query_skill("xiaowuxiang", 1) < 100 )
                        return notify_fail("你的小无相功修为不足，使不出「九羽天诛」绝技。\n");
                if ( me->query_skill_mapped("force") != "xiaowuxiang" )
                        return notify_fail("你没有使用小无相功，无法使用「九羽天诛」绝技。\n");
        }

        else
        {
                if ( me->query_skill("bahuang-gong", 1) < 100 )
                        return notify_fail("你的八荒六合惟我独尊功修为不足，使不出「九羽天诛」绝技。\n");
                if ( me->query_skill_mapped("force") != "bahuang-gong" )
                        return notify_fail("你没有使用八荒六合惟我独尊功，无法使用「九羽天诛」绝技。\n");
        }

        if( query_temp("09_pfm/zhu", me) )
                return notify_fail("你正在使用「九羽天诛」。\n");

        if( query_temp("09_pfm/yun_duzun", me) )
                return notify_fail("你正在运用「惟我独尊」心法，无法使用「九羽天诛」！\n");

        if( query_temp("09_pfm/zhu_over", me) )
                return notify_fail("你刚刚使用过「九羽天诛」，此时气血不调，还是等一下再用吧。\n");

        bonus = me->query_skill("tianyu-qijian", 1) / 10;
        bonus += me->query_skill("sword", 1) /10;
        bonus += me->query_skill("piaomiao", 1) /10;

        addn_temp("apply/attack", bonus, me);
        addn_temp("apply/damage", bonus*2, me);
        addn_temp("apply/defense", bonus, me);

        message_combatd(HIR"\n只听一声宝剑破空的龙吟之声，$N手中的"+weapon->name()+HIR"顿时闪烁出耀眼的光芒，一股股寒气弥\n"+
                          "漫于周身。忽然$N招式徒然一快，使出一招「"HIW"九羽天诛"HIR"」，霎时间满天剑影铺天盖地，\n"+
                          "仿佛三九天的鹅毛大雪扑面而来，直压向$n的周身要害，速度更是快得惊人！\n"NOR, me, target);

        hits = bonus/3;

        if ( hits < 3 )
                hits = 3;
        if ( hits > 9 )
                hits = 9;

        set_temp("09_pfm/zhu", hits, me);
        addn("neili", -200, me);

        remove_call_out("check_fight");
        call_out("check_fight", 1, me, target, bonus);

        return 1;
}

void remove_effect(object me, int bonus)
{
        addn_temp("apply/attack", -bonus, me);
        addn_temp("apply/damage", -bonus*2, me);
        addn_temp("apply/defense", -bonus, me);
        delete_temp("09_pfm/zhu", me);
        delete_temp("09_pfm/zhu_hit_done", me);
        set_temp("09_pfm/zhu_over", 1, me);
        if ( me->is_fighting() )
                me->start_busy(3);

        remove_call_out("zhu_done");
        call_out("zhu_done", 12, me);
}

void zhu_done(object me)
{
        if ( !me )
                return;

        tell_object(me, HIY"经过一段时间的休息，你又可以使用「九羽天诛」了！\n"NOR);
        delete_temp("09_pfm/zhu_over", me);
}

void check_fight(object me, object target, int bonus)
{
        if ( !me )
                return;

        if( !me->is_fighting() || !query_temp("09_pfm/zhu", me) || query_temp("09_pfm/zhu", me)<1
             || !target || !living(target) )
        {
                message_combatd(WHT"\n$N长舒了一口气，手中的剑光也以不似先前一般凌厉了。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if( query("neili", me)<300 )
        {
                message_combatd(HIR"\n$N额头冒汗，看来是内力不随，剑锋上的光芒一下消失不见了。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if ( me->query_skill_mapped("sword") != "tianyu-qijian" )
        {
                message_combatd(HIR"\n$N忽然招式一边，剑上的光芒顿时消失得无影无踪。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if( !query_temp("weapon", me) )
        {
                tell_object(me, HIR"\n你的兵器不见了，无法继续使用「九羽天诛」了。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        remove_call_out("check_fight");
        call_out("check_fight", 1, me, target, bonus);
}

int help(object me)
{
        write(WHT"\n「九羽天诛」\n\n"CYN+
                 " 　　九羽天诛，招如其名，施展开来时犹如满天鹅毛飘零而下，剑气纵横\n"+
                 " 剑影如雪，将敌人前后左右上下围住，使其避无可避，退无可退。这一招\n"+
                 " 剑法初时只能连发三招，然而当功力有成之时则最多可连出九招，前后一\n"+
                 " 气呵成，连绵不绝，将敌人压在一层层巨浪之下，实是厉害不过。\n\n"+

                 " "HIR"注"WHT"：此招不可与「惟我独尊」心法同时使用。\n\n"+

              WHT" 要求：八荒六合唯我独尊功　"HIR"100"WHT" 级\n"+
              WHT" 　　　小无相功          　"HIR"100"WHT" 级\n"+
              WHT" 　　　天羽奇剑  　　　　　"HIR"100"WHT" 级\n"+
              WHT" 　　　基本剑法　　　　　　"HIR"100"WHT" 级\n"+
              WHT" 　　　当前内力  　　　　 "HIR" 400"WHT" 点\n"+
              WHT" 　　　最大内力　　　　　 "HIR"1000"WHT" 点\n\n"+

              WHT" 战斗中使用。\n"NOR);

        return 1;
}