// This program is a part of NITAN MudLIB
// xian.c 神龙再现

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "神龙再现"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        string skill;
        int ap, pp, dp, damage;
        int delta;
        int fmsk = me->query_skill("mukong-yiqie", 1);

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「神龙再现」只能对战斗中的对手使用。\n");

        if (me->query_skill("shedao-qigong", 1) < 120)
                return notify_fail("你的蛇岛奇功修为有限，不能使用「神龙再现」！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，无法运用「神龙再现」！\n");

        if( objectp(weapon=query_temp("weapon", me)) &&
            query("skill_type", weapon) != "staff" &&
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的兵器不对，怎么使用「神龙再现」！\n");

        if (weapon)
                skill=query("skill_type", weapon);
        else
                skill = "unarmed";

        if (me->query_skill_mapped(skill) != "shedao-qigong")
                return notify_fail("你没有将" + (string)to_chinese(skill)[4..<1] +
                                   "激发为蛇岛奇功, 不能使用「神龙再现」！\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        switch (skill)
        {
        case "unarmed":
                msg = HIW "$N" HIW "轻身一跃，已然逼近$n" HIW "随即一掌向$p"
                      HIW "肩头按去，虚虚实实，暗藏千百变化。\n" NOR;
                break;

        case "sword":
                msg = HIW "$N" HIW "足不点地，飘然欺身上前，一剑刺出，" +
                      weapon->name() + HIW "直指$n" HIW "腰间。" NOR;
                break;

        case "staff":
                msg = HIW "$N" HIW "手中" + weapon->name() +
                      HIW "吞吞吐吐，虚虚实实，化作一团光影，斜斜扫向$n"
                      HIW "腰间。\n" NOR;
                break;
        }

        ap = attack_power(me, skill);
        pp = defense_power(target, "parry");
        dp = defense_power(target, "dodge");

        damage = damage_power(me, skill);
        damage+= query("jiali", me);
        
        delta = ABILITY_D->check_ability(me, "ap_power-sdqg-xian"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        delta = ABILITY_D->check_ability(me, "da_power-sdqg-xian"); // 门派ab
        if( delta ) damage += damage*delta/100;
                
        if (ap / 2 + random(ap) > pp)
        {
                addn("neili", -150, me);
                me->start_busy(2);

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50+fmsk/50,
                                           HIR "$n" HIR "欲架不能，欲躲不得，一个闪失"
                                           "，被$P" HIR "打了个正中，鲜血迸流。\n" NOR);
        } else
        if (ap / 3 + random(ap) > dp)
        {
                addn("neili", -180, me);
                me->start_busy(2);

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 55+fmsk/50,
                                           HIR "$n" HIR "见$P" HIR "这招极为精妙，不敢"
                                           "抵挡，慌忙后退跃开，却见$P" HIR "招式一变，竟然料敌在先，\n"
                                           "一招正中$p" HIR "，直打了个鲜血四下飞溅。\n" NOR);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "$n" CYN "不敢怠慢，见招拆招，接连破去$P"
                       CYN "后续三十六道变化，不漏半点破绽。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}


