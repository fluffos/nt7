// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "亢龙有悔" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int delta;
        int fmsk = me->query_skill("bixue-danxin", 1);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手使用。\n");

        if ((int)me->query_skill("force") < 260)
                return notify_fail("你内功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你内力修为不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("dragon-strike", 1) < 240)
                return notify_fail("你降龙十八掌火候不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("你没有激发降龙十八掌，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("你没有准备降龙十八掌，难以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        // 第一掌
        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;
        
        delta = ABILITY_D->check_ability(me, "ap_power-xlz-hui"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        damage = damage_power(me, "strike");
        damage+= query("jiali", me);
        
        delta = ABILITY_D->check_ability(me, "da_power-xlz-hui"); // 门派ab
        if( delta ) damage += damage*delta/100;
        
        message_combatd(sort_msg(HIW "\n忽然间$N" HIW "身形激进，左手一划，右手呼的一掌，便"
                     "向$n" HIW "击去，正是降龙十八掌「" NOR + HIY "亢龙有悔" NOR
                     + HIW "」一招，力自掌生之际说到便到，以排山倒海之势向$n" HIW
                     "狂涌而去，当真石破天惊，威力无比。\n" NOR), me, target);
        if (ap / 2 + random(ap) + fmsk > dp)
        {
                msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 75,
                                          HIR "$p" HIR "一楞，只见$P" HIR "身形"
                                          "一闪，已晃至自己跟前，躲闪不及，被击"
                                          "个正中。\n:内伤@?");


        } else
        {
                msg = HIC "$p" HIC "气贯双臂，凝神应对，游刃有余，$P"
                      HIC "掌力如泥牛入海，尽数卸去。\n" NOR;
        }
        message_combatd(msg, me, target);
        
        // 第二掌
        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "parry") + target->query_int()*10;
        delta = ABILITY_D->check_ability(me, "ap_power-xlz-hui"); // 门派ab
        if( delta ) ap += ap*delta/100;

        message_combatd(sort_msg(HIW "\n$N" HIW "一掌既出，身子已然抢到离$n" HIW "三四丈之外"
                     "，后掌推前掌，两股掌力道合并，又是一招「" NOR + HIY "亢龙有"
                     "悔" NOR + HIW "」攻出，掌力犹如怒潮狂涌，势不可当。霎时$n"
                     HIW "便觉气息窒滞，立足不稳。\n" NOR), me, target);
        if (ap / 2 + random(ap) + fmsk > dp)
        {
                msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 85,
                                           HIR "只听$p" HIR "一声惨嚎，被$P" HIR
                                           "一掌击中胸前，“喀嚓喀嚓”断了几根肋"
                                           "骨。\n:内伤@?");

        } else
        {
                msg = HIC "$p" HIC "气贯双臂，凝神应对，游刃有余，$P"
                      HIC "掌力如泥牛入海，尽数卸去。\n" NOR;
                
        }
        message_combatd(msg, me, target);
        // 第三掌
        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "force") + target->query_con()*10;
        delta = ABILITY_D->check_ability(me, "ap_power-xlz-hui"); // 门派ab
        if( delta ) ap += ap*delta/100;

        message_combatd(sort_msg(HIW "\n紧跟着$N" HIW "一声暴喝，右掌斜斜挥出，前招掌力未消"
                     "，此招掌力又到，竟然又攻出一招「" NOR + HIY "亢龙有悔" NOR
                     + HIW "」，掌夹风势，势如破竹，便如一堵无形气墙，向前疾冲而"
                     "去。$n" HIW "只觉气血翻涌，气息沉浊。\n" NOR), me, target);

        if (ap / 2 + random(ap) + fmsk > dp)
        {
                msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 95,
                                           HIR "结果$p" HIR "躲闪不及，$P" HIR
                                           "的掌劲顿时穿胸而过，“哇”的喷出一大"
                                           "口鲜血。\n:内伤@?");

        } else
        {
                msg = HIC "$p" HIC "见这招来势凶猛，身形疾退，瞬间飘出三"
                      "丈，脱出$P" HIC "掌力之外。\n" NOR;
        }

        message_combatd(msg, me, target);
        addn("neili", -400-random(600), me);
        me->start_busy(3 + random(4));
        return 1;
}
