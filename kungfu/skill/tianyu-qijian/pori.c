// This program is a part of NITAN MudLIB
// pori.c 九弧破日

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "九弧破日"; }

int perform(object me, object target)
{
        object weapon;
        int damage, p, i, wadd;
        string msg;
        int ap, dp;

        weapon=query_temp("weapon", me);

        if ( ! target )
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if ( ! target || ! me->is_fighting(target) )
                return notify_fail("「九弧破日」只能对战斗中的对手使用。\n");

        if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("你手里没有剑，无法使用「九弧破日」绝技！\n");

        if ( me->query_skill_mapped("sword") != "tianyu-qijian"
                || me->query_skill_mapped("parry") != "tianyu-qijian" )
                return notify_fail("你没有用天羽奇剑，怎么施展「九弧破日」绝技？\n");

        if( query("unique", weapon) )
                return notify_fail("你手中乃是一柄宝剑，无法用内力震碎！\n");

        if ( me->query_skill("tianyu-qijian", 1) < 160 )
                return notify_fail("你的天羽奇剑火候不足，使不出「九弧破日」绝技。\n");

        if ( me->query_skill("sword", 1) < 140 )
                return notify_fail("你的基本剑法还不够娴熟，使不出「九弧破日」绝技。\n");

        if( query("09g/ring", me) == "li" )
        {
                if ( me->query_skill("xiaowuxiang", 1) < 140 )
                        return notify_fail("你的小无相功修为不足，使不出「九弧破日」绝技。\n");
                if ( me->query_skill_mapped("force") != "bahuang-gong" )
                        return notify_fail("你没有使用小无相功，无法使用「九弧破日」绝技。\n");
        }

        else
        {
                if ( me->query_skill("bahuang-gong", 1) < 140 )
                        return notify_fail("你的八荒六合惟我独尊功修为不足，使不出「九弧破日」绝技。\n");
                if ( me->query_skill_mapped("force") != "bahuang-gong" )
                        return notify_fail("你没有使用八荒六合惟我独尊功，无法使用「九弧破日」绝技。\n");
        }

        if ( me->query_str() < 28 )
                return notify_fail("你的膂力还不够强劲，使不出「九弧破日」绝技。\n");

        if ( me->query_dex() < 30 )
                return notify_fail("你的身法还不够轻灵，无法施展「九弧破日」绝技。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力修为不足，无法使用「九弧破日」绝技。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的内力不够，无法震碎手中长剑。\n");


        msg = HIY"\n$N手腕一抖，手中"+weapon->name()+HIY"立时被内力震断，无数碎片如雨点般激射向$n！\n"NOR;

        //Damage is also decided by how many times the player used this perform
        i=query("09g/pori", me);

        if ( i > me->query_skill("tianyu-qijian") )
                i = me->query_skill("tianyu-qijian");

        i-=query("age", me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");
        if( ap / 2 + random(ap) > dp )
        {
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(1);
                addn("neili", -300, me);
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                damage+= i*20;

                //Damage is also decided by how strong the weapon is
                wadd=(query("weapon_prop/damage", weapon)+1);
                damage = damage+(random(wadd)+wadd)*2;

                if( query("neili", me)>query("neili", target)*2 )
                        damage += random(damage);

                if ( damage > 2000 )
                        damage = damage+random(me->query_skill("sword", 1));

                if ( damage < 200 )
                        damage = damage-random(target->query_skill("dodge", 1)/2);

                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);

                msg += HIR"\n结果$N手中射出的"+weapon->name()+
                       HIR"碎片尽数钉在了$n身上，一屡屡鲜血从伤口处涌出！\n"NOR;

                p=query("qi", target)*100/query("max_qi", target);
                msg = replace_string(msg, "$w", "碎片");
                msg = replace_string(msg, "$l", "周身多处");

                if ( me->query_skill("tianyu-qijian", 1) > 140
                && me->query_skill("sword") > 140 )
                        call_out("perform2", 0, me, target);
        }

        else
        {
                addn("neili", -100, me);

                me->start_busy(3);
                msg += HIC"\n$n眼见"+weapon->name()+
                       HIC"碎片已射至眼前，只得铤而走险，运劲鼓起袍袖将碎片拨了开！\n"NOR;
        }

        message_combatd(msg, me, target);

        weapon->unequip();
        weapon->move(environment(me));
        set("name", "碎裂的"+query("name", weapon), weapon);
        set("value", 1, weapon);
        set("weapon_prop", 0, weapon);
        me->reset_action();
        addn("09g/pfm_pori", 1, me);

        return 1;
}

//If possible, also busy target
int perform2(object me, object target)
{
        string msg;

        if ( !me || !target || !living(target) )
                return 0;

        msg = MAG "\n不料，$N射出的碎片竟运上了阴柔内力，钉向了$n的周身要穴！\n\n"NOR;

        if( query("max_neili", me)>query("max_neili", target)*2/3 && random(10)<4 )
        {
                msg += HIR "结果$n只觉伤处气血闭塞，真气已经无法流转，登时倒抽一口冷气！\n" NOR;
                me->start_busy(3);
                target->start_busy(me->query_skill("force",1)/10);
                addn("neili", -(me->query_skill("force",1)/5), me);
        }

        else
        {
                addn("neili", -10, me);
                addn("neili", -10, target);
                me->start_busy(3);
                msg += HIC "\n$p只觉碎片上运有阴柔内力，意欲打穴封脉。幸而早有准备，没有上当。\n" NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}

int help(object me)
{
        write(WHT"\n「九弧破日」\n\n"CYN+
                 " 　　这一式九弧破日乃是天羽奇剑的厉害招式，系以深厚内功震碎自己的\n"+
                 " 兵器，并以满天花雨的手法抛向敌人，实是厉害不过。然而，此招需有深\n"+
                 " 厚内功作基础，并需相当的剑法造诣才能得以施展。也正因手上劲道不好\n"+
                 " 掌握，因此这一招的威力及命中率需靠"HIY"经常地使用"CYN"来提高，招式的威力与\n"+
                 " 所使用的武器质量也有很大关系。不仅如此，当剑法的造诣达到一定境界\n"+
                 " 之时还会出现"HIG"附加功效"CYN"。\n\n"+

              WHT" 要求：八荒六合唯我独尊功　"HIR"140"WHT" 级\n"+
              WHT" 　　　小无相功          　"HIR"140"WHT" 级\n"+
              WHT" 　　　天羽奇剑  　　　　　"HIR"160"WHT" 级\n"+
              WHT" 　　　基本剑法　　　　　　"HIR"140"WHT" 级\n"+
              WHT" 　　　缥缈心法  　　　　　"HIR" 80"WHT" 级\n"+
              WHT" 　　　后天膂力  　　　　  "HIR" 28"WHT" 点\n"+
              WHT" 　　　后天身法  　　　　  "HIR" 30"WHT" 点\n"+
              WHT" 　　　当前精力  　　　　 "HIR" 200"WHT" 点\n"+
              WHT" 　　　当前内力  　　　　 "HIR"1000"WHT" 点\n"+
              WHT" 　　　最大内力　　　　　 "HIR"2000"WHT" 点\n\n"+

              WHT" 战斗中使用。\n"NOR);

        return 1;
}
