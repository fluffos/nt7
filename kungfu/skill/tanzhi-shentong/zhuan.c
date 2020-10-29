#include <ansi.h>
#include <combat.h>

string name() { return HIR "转乾坤" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;
        int fmsk;
        int delta;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 220)
                return notify_fail("你的弹指神通不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("qimen-wuxing", 1) < 200)
                return notify_fail("你的奇门五行修为不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你没有激发弹指神通，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你没有准备弹指神通，难以施展" + name() + "。\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "将全身功力聚于一指，指劲按照二十八宿方位云贯而出，正"
              "是桃花岛「" HIR "转乾坤" HIC "」绝技。\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("qimen-wuxing", 1);
        dp = defense_power(target, "dodge") + target->query_skill("qimen-wuxing", 1);
        fmsk = me->query_skill("qimen-xuanshu", 1); 
        
        delta = ABILITY_D->check_ability(me, "ap_power-tzst-zhuan"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        if (ap / 2 + random(ap) + fmsk > dp) 
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        msg += HIR "霎那间$n" HIR "只见寒芒一闪，$N" HIR "食指"
                               "已钻入$p" HIR "印堂半尺，指劲顿时破脑而入。\n"
                               HIW "你听到“噗”的一声，身上竟然溅到几滴脑浆！"
                               "\n" NOR "( $n" RED "受伤过重，已经有如风中残烛"
                               "，随时都可能断气。" NOR ")\n";
                        message_combatd(msg, me, target); 
                        damage = -1;
                } else
                if (query_temp("thd/tz", me) && random(3) != 1) 
                {
                        damage = damage_power(me, "finger");
                        damage+= query("jiali", me);
                        delta = ABILITY_D->check_ability(me, "da_power-tzst-zhuan"); // 门派ab
                        if( delta ) damage += damage*delta/100;
                        msg += HIY "\n眼看到$n" HIY "已被点中要穴" 
                               ",$N强提一口真气，手双交错点出，一道道指气\n"  
                               "顿时将$n逼的退无可退！\n\n" NOR; 
                        
                        for (int i = 0; i < (int)random(9); i++) 
                        {
                                if (! me->is_fighting(target))  
                                        break;  
                                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100+fmsk/10, 
                                        HIR "霎那间$n" HIR "只见寒芒一闪，$N" 
                                        HIR "食指已钻入$p" HIR "胸堂半尺，指劲"  
                                        "顿时破体而入。\n你听到“嗤”的一声，"  
                                        "身上竟然溅到几滴鲜血！\n" NOR); 
                        }
                        message_combatd(msg, me, target); 
                        addn("neili", -300, me);
                        me->start_busy(1 + random(5)); 
                } else
                {
                        me->start_busy(5);
                        damage = damage_power(me, "finger");
                        damage+= query("jiali", me);
                        damage *= 6;
                        delta = ABILITY_D->check_ability(me, "da_power-tzst-zhuan"); // 门派ab
                        if( delta ) damage += damage*delta/100;
                        addn("neili", -500, me);
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 175 + fmsk / 10, 
                                                   HIR "霎那间$n" HIR "只见寒芒一闪，$N"
                                                   HIR "食指已钻入$p" HIR "胸堂半尺，指劲"
                                                   "顿时破体而入。\n你听到“嗤”的一声，"
                                                   "身上竟然溅到几滴鲜血！\n" NOR);
                        message_combatd(msg, me, target); 
                }
        } else
        {
                me->start_busy(4);
                addn("neili", -300, me);
                msg += CYN "$p" CYN "见$P" CYN "招式奇特，不感大"
                       "意，顿时向后跃数丈，躲闪开来。\n" NOR;
                message_combatd(msg, me, target); 
        }

        if (damage < 0)
        {
                target->die(me);
        }

        return 1;
}
