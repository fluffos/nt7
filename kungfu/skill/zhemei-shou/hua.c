// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

string name() { return HIR "化妖功" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp, p;
        int lv, cost_neili;
        int delta;
        int fmsk = me->query_skill("fanlao-huantong", 1)+me->query_skill("xiaoyao-you", 1);

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("beiming-shengong", 1) < 220
        &&  (int)me->query_skill("xiaowuxiang", 1) < 220
        &&  (int)me->query_skill("bahuang-gong", 1) < 220)
                return notify_fail("你的北冥神功火候不够，难以施展" + name() + "。\n");

        if (lv = (int)me->query_skill("zhemei-shou", 1) < 220)
                return notify_fail("你逍遥折梅手等级不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你现在真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIM "$N" HIM "深深吸进一口气，单手挥出，掌缘顿时霞光万道，漾出"
              "七色虹彩向$n" HIM "席卷而至。\n" NOR;

        ap = attack_power(me, "hand") + me->query_skill("dodge");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (target->is_bad() || ! userp(target))
                ap += ap / 10;
        
        ap += fmsk;
        delta = ABILITY_D->check_ability(me, "ap_power-zms-hua"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                lv = me->query_skill("zhemei-shou", 1);
                if (lv >= 220)cost_neili = -500;
                if (lv >= 240)cost_neili = -470;
                if (lv >= 260)cost_neili = -440;
                if (lv >= 280)cost_neili = -400;
                if (lv >= 300)cost_neili = -360;
                if (lv >= 320)cost_neili = -320;
                if (lv >= 340)cost_neili = -300;
                if (lv >= 360)cost_neili = -270;
                if (lv >= 400)cost_neili = -200;
                if( !playerp(target) && query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIM "只听$n" HIM "一声尖啸，$N" HIM "的七色掌"
                               "劲已尽数注入$p" HIM "体内，顿时将$p" HIM "化"
                               "为一滩血水。\n" NOR "( $n" RED "受伤过重，已"
                               "经有如风中残烛，随时都可能断气。" NOR ")\n";
                        damage = -1;
                        addn("neili", cost_neili, me);
                        me->start_busy(1);
                } else
                {
                        damage = damage_power(me, "hand");
                        damage+=query("jiali", me);
                        damage+=damage/300*me->query_str();
                        damage+=me->query_all_buff("unarmed_damage");
                        damage*=4;
                        
                        delta = ABILITY_D->check_ability(me, "da_power-zms-hua"); // 门派ab
                        if( delta ) damage += damage*delta/100;
        
/*
                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage / 2, me);
                        target->receive_damage("jing", damage / 4, me);
                        target->receive_wound("jing", damage / 8, me);
                        p=query("qi", target)*100/query("max_qi", target);
*/

                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200+fmsk/15,
                                HIM "$n" HIM "只是微微一愣，$N" HIM "的七色掌劲已破体而"
                                "入，$p" HIM "便犹如身置洪炉一般，连呕数口鲜血。\n" NOR);
                        //msg += "( $n" + eff_status_msg(p) + " )\n";

                        addn("neili", cost_neili, me);
                }
        } else
        {
                msg += CYN "$p" CYN "见状大惊失色，完全勘破不透$P"
                       CYN "招中奥秘，当即飞身跃起丈许，躲闪开来。\n" NOR;
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        if (damage < 0)
        {
                target->receive_damage("qi", 100, me);
                target->die(me);
        }

        me->start_busy(3);
        return 1;
}
