// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "夺魂势" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("force", 1) < 130)
                return notify_fail("你的内功火候不够，使不了" + name() + "。\n");

        if (me->query_skill("chanhun-suo", 1) < 100)
                return notify_fail("你的缠魂索功力太浅，使不了" + name() + "。\n");

        if( query("neili", me)<220 )
                return notify_fail("你的真气不够，无法使用" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "chanhun-suo")
                return notify_fail("你没有激发缠魂索法，使不了" + name() + "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "诡异的一笑，手中" + weapon->name() +
              HIY "抖得笔直，劈向$n" HIY "手腕，可是待到中途却又停滞，转往$n"
              HIY "胸口挥去！\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");
                addn("neili", -180, me);
                me->start_busy(2);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "结果$n" HIR "一声惨叫，未能看破$N"
                                           HIR "的企图，被这一鞭硬击在胸口，鲜血飞"
                                           "溅，皮肉绽开！\n" NOR);
                message_combatd(msg, me, target);
                // if (ap > 1000) ap = 1000;
                dp += target->query_skill("martial-cognize", 1) * 2;
                if (! target->is_busy() &&
                    //query("material", weapon) == "white silk" &&
                    ap / 2 + random(ap) > dp)
                {
                        target->start_busy(3 + random(4));
                        message_vision(HIW "$N" HIW "一抖，手中的" + weapon->name() +
                                       HIW "“嗖“的串了出来，隐隐然缠向$n"
                                       HIW "。\n$n" HIW "大吃一惊，急忙退后，闪去这一招。\n" NOR,
                                       me, target);
                }
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "飞身一跃而起，躲避开了"
                       CYN "$P" CYN "的攻击！\n" NOR;
                message_combatd(msg, me, target);
        }

        return 1;
}