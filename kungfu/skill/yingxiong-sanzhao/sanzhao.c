//sanzhao.c 夺命三连招

#include <combat.h>
#include <ansi.h>

inherit F_SSERVER;

string name() { return "夺命三连招"; }

string *limbs =
({
        "头顶", "颈部", "胸口", "后心", "左肩", "右肩", "左臂",
        "右臂", "左手", "右手", "两肋", "左脸", "腰间", "小腹",
        "左腿", "右腿", "右脸", "左脚", "右脚", "左耳", "右耳"
});
void chkpfm(object me, object target, int amount);

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        object weapon, weapon1;
        int lvl1, lvl2, amount;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("夺命三连招只能对战斗中的对手使用。\n");

        if (!living(target))
                return notify_fail("他已经晕倒了，你可以轻易地杀了他！\n");

        if( time()-query_temp("sxj-t", target)<30 )
                return notify_fail("他已经适应了你的招式，对他来说已经无效了！\n");

        if( me->query_skill_mapped("force") != "shenlong-xinfa" &&
            me->query_skill_mapped("force") != "busi-shenlong" )
                return notify_fail("你所用的并非神龙心法，无法施展夺命三连招！\n");

        if (me->query_skill_mapped("strike") != "yingxiong-sanzhao")
                return notify_fail("你没有激发英雄三招，难以施展夺命三连招。\n");

        if (me->query_skill_prepared("strike") != "yingxiong-sanzhao")
                return notify_fail("你没有准备英雄三招，难以施展夺命三连招。\n");

        if( (lvl1=me->query_skill("shenlong-xinfa", 1)) < 150 &&
            me->query_skill("busi-shenlong",1)< 150)
                return notify_fail("你的神龙心法火候未到，无法施展夺命三连招！\n");

        if( (lvl2=me->query_skill("strike")) < 200 )
                return notify_fail("你英雄三招修为不足，还不会使用夺命三连招！\n");

        if( (lvl2 - lvl1) < lvl2 / 4 && lvl1 < 200)
                return notify_fail("夺命三连招需要更精湛的武艺！\n");

        amount = (lvl1+lvl2) / 5;

        if ( amount < 60 ) amount = 60;
        if ( amount > 200 ) amount = 200;

        if( query("neili", me) <= amount*10 )
                return notify_fail("你的内力不够使用夺命三连招！\n");

        if( query("jingli", me) <= amount*5 )
                return notify_fail("你的精力不够使用夺命三连招！\n");

        if( !query_temp("sanxianjian", me)){
                data = ([
                        "unarmed_damage": amount*2,
                        "attack": amount,
                        "dodge" : amount,
                ]);
                set_temp("sanxianjian", 1, me);
                buff = ([
                        "caster": me,
                        "target": me,
                        "type"  : "yxsz_sanzhao",
                        "attr"  : "bless",
                        "name"  : "英雄三招·夺命三连招",
                        "time"  : amount/10,
                        "buff_data": data,      
                        "buff_msg" : "",
                        "disa_msg" : HIY "\n$N收回内劲,招式也恢复了平常。\n" NOR,
                        "disa_type": 1,
                        
                ]);
                BUFF_D->buffup(buff);
                me->start_busy(1);
        }

        message_combatd(HIW "$n抓住$N的后颈，一把提起。$N左手慢慢反转，在$n左腋底搔了一把，\n$n身子软了下来，$N左手拿住$n腋下，右手慢慢回转，抓住$n领口，缓缓\n举起$n的身子，过了自己头顶，向外摔出。\n"NOR, me, target);
        chkpfm(me, target, amount);
        message_combatd(HIW "$N俯伏地上，$n伸右足踏住$N的后腰，$N双腿一缩，似欲跪拜，\n右臂却慢慢横掠而出，突然间一个筋斗，向$n的胯下钻去，只一作势\n左手已抓住$n右脚足踝，右手向$n小腹击去。\n"NOR, me, target);
        chkpfm(me, target, amount);
        set_temp("sxj-c", 3, me);
        message_combatd(HIW"$N双臂反在背后，突然双手十指弯起，各成半球之形，身子向后一撞\n十指便抓向$n的胸部，$n向后一缩，$N突然一个倒翻筋斗，身子跃起\n双腿一分，已跨在$n肩头，同时双手按指压住$n太阳穴，食指按眉，中指按眼！\n"NOR, me, target);
        chkpfm(me, target, amount);



        if( query("eff_qi", target)*100/query("max_qi", target) <= 20
          && query("qi", target)*100/query("max_qi", target) <= 5
          && query_temp("sxj-c", me) == 3 )
        {
                message_combatd(HIR "\n$N"+HIR+"这招内劲所注，力道强横之极，$n便如被凌空飞来的重锤扫到，当下喷出一口鲜血！！\n" NOR, me, target);
                target->die(me);
        }

        me->start_busy(2);
        return 1;
}
void chkpfm(object me, object target, int amount)
{
        object weapon2=query_temp("weapon", target);
        string attack_skill, dodge_skill, parry_skill, result, msg = "";
        int ap, dp, pp, damage, level;

        if( !me->is_fighting(target) || !living(target) )
                return;

        level = me->query_skill("yingxiong-sanzhao", 1);
        damage = amount+random(level)/2;
        ap = COMBAT_D->skill_power(me, "strike", SKILL_USAGE_ATTACK)/ 100;
        if( ap < 1) ap = 1;

        dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE)/ 100;
        if( target->is_busy() ) dp /= 3;
        if( dp < 1 ) dp = 1;
        if( random(ap + dp) < dp )
        {
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg();
        }
        else
        {
                pp = COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE)/100;
                if( target->is_busy() ) pp /= 2;
                if( pp < 1 ) pp = 1;

                if( random(ap + pp) < pp )
                {
                        parry_skill = target->query_skill_mapped("parry");
                        if( !parry_skill || !SKILL_D(parry_skill)->parry_available())
                                parry_skill = "parry";
                        msg += SKILL_D(parry_skill)->query_parry_msg(weapon2, target);
                }
                else
                {
                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage/3, me);
                        if( query_temp("sxj-c", me) == 3 )
                                result = COMBAT_D->damage_msg(damage, "瘀伤");
                        else result = COMBAT_D->damage_msg(damage, "瘀伤");
                        msg += result;
                        result=COMBAT_D->status_msg(query("qi", target)*100/
                                query("max_qi", target));
                        msg += "( $n"+result+" )\n";
                        target->start_busy(1);
                }
        }
        result = limbs[random(sizeof(limbs))];
        msg = replace_string( msg, "$l", result );
        message_combatd(msg, me, target);
}
