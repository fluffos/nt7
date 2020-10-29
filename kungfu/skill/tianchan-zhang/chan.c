#include <ansi.h>
#include <combat.h>

string name() { return HIR "毒蟾掌" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;
        int damage, lvl;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必须是空手才能使用" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "tianchan-zhang")
                return notify_fail("你没有激发天蟾掌法，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "tianchan-zhang")
                return notify_fail("你没有准备使用天蟾掌法，难以施展" + name() + "。\n");

        lvl = me->query_skill("tianchan-zhang", 1);

        if (lvl < 120)
                return notify_fail("你天蟾掌法不够纯熟，难以施展" + name() + "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的内功火候太低，，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的内力不够，，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "一声冷笑，聚气于掌，飞身一跃而起，一招"
                  "携满剧毒的「毒蟾掌」对着$n" HIR "凌空拍下！\n"NOR;

        ap = attack_power(me, "strike") + lvl;
        dp = defense_power(target, "parry");

        if ( ap / 2 + random(ap) > dp )
        {
                addn("neili", -200, me);
                damage = damage_power(me, "strike");
                target->affect_by("tianchan_zhang", ([
                        "level":query("jiali", me)+random(query("jiali", me)),
                        "id":query("id", me),
                        "duration" : lvl / 60 + random(lvl / 30)
                ]));
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70,
                        HIR "只听$n" HIR "惨叫一声，被$N" HIR "这一掌"
                        "拍个正着，顿时毒气攻心，“哇”地喷出一大口鲜血。\n" NOR);

                me->start_busy(2);
        } else
        {
                msg += HIY "$p" HIY "见$P" HIY "来势汹涌，急忙纵身一跃而起，躲"
                       "开了这一击！\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}