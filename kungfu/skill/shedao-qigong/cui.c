// This program is a part of NITAN MudLIB
// cui.c 摧心断肠

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "摧心断肠"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        string skill;
        int ap, fp, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「摧心断肠」只能对战斗中的对手使用。\n");

        if (me->query_skill("shedao-qigong", 1) < 120)
                return notify_fail("你的蛇岛奇功修为有限，不能使用「摧心断肠」！\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真气不够，无法运用「摧心断肠」！\n");

        if( objectp(weapon=query_temp("weapon", me)) &&
            query("skill_type", weapon) != "staff" &&
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的兵器不对，怎么使用「摧心断肠」！\n");

        if (weapon)
                skill=query("skill_type", weapon);
        else
                skill = "unarmed";

        if (me->query_skill_mapped(skill) != "shedao-qigong")
                return notify_fail("你没有将" + (string)to_chinese(skill)[4..<1] +
                                   "激发为蛇岛奇功, 不能使用「摧心断肠」！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        switch (skill)
        {
        case "unarmed":
                msg = HIW "$N" HIW "一声暴喝，双掌一起击出，霎时间飞砂走石，$n"
                      HIW "只觉得几乎窒息。\n" NOR;
                break;

        case "sword":
                msg = HIW "$N" HIW "一声暴喝，手中" + weapon->name() +
                      HIW "直劈而下，只听呼啸声大作，地上的尘土受内力所激纷纷飞扬而起。\n" NOR;
                break;

        case "staff":
                msg = HIW "$N" HIW "一声暴喝，手中" + weapon->name() +
                      HIW "横扫荡出，一时间尘土飞扬，$n"
                      HIW "登时觉得呼吸不畅。\n" NOR;
                break;
        }

        ap = attack_power(me, skill);
        fp = defense_power(target, "force");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) < fp)
        {
                addn("neili", -200, me);
                msg += CYN "可是$n" CYN "内功深厚，奋力接下$N"
                       CYN "这一招，丝毫无损。\n" NOR;
                me->start_busy(2);
        } else
        if (ap / 2 + random(ap) < dp)
        {
                addn("neili", -50, me);
                msg += CYN "$n" CYN "哈哈一笑，飘身跃开，让$N"
                       CYN "这一招全然落空。\n" NOR;
                me->start_busy(3);
        } else
        {
                addn("neili", -220, me);
                me->start_busy(2);
                damage = damage_power(me, skill);
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
                                           HIR "$n" HIR "只觉得$N" HIR "内力犹如"
                                           "排山倒海一般，怎能抵挡？“哇”的一下吐出一大口鲜血。\n" NOR);
        }
        message_combatd(msg, me, target);

        return 1;
}


