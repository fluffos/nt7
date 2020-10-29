// wuji.c 混元无极

#include <ansi.h>
#include <combat.h>

string name() { return HIW "混元无极" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        skill = me->query_skill("hunyuan-zhang", 1);

        if (skill < 120)
                return notify_fail("你的混元掌等级不够, 不能施展" + name() + "！\n");

        if (me->query_skill("force", 1) < 120)
                return notify_fail("你内功修为不够，无法施展" + name() + "！\n");

        if( query("max_neili", me)<1400 )
                return notify_fail("你内力修为不足，无法施展" + name() + "！\n");

        if( query("neili", me)<240 )
                return notify_fail("你的内力不够，无法施展" + name() + "！\n");

        if (me->query_skill_prepared("strike") != "hunyuan-zhang")
                return notify_fail("你没有准备使用混元掌，无法施展" + name() + "！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "怒喝一声，潜运「" HIW "混元无极" HIC "」，双拳挟"
              "着隐隐的风雷之声向$n" HIC "击去。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -220, me);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "只觉得胸前一阵剧痛，“哇”的一"
                                           "声喷出一口鲜血！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -120, me);
                msg += CYN "只见$n" CYN "不慌不忙，轻轻一闪，躲过"
                       "了$N" CYN "的必杀一击！\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}