#include <ansi.h>
#include <combat.h>

#define DAN "「" HIR "弹射毒药" NOR "」"

inherit F_SSERVER;

int exert(object me, object target)
{
        object du;
        int lvl, lvp, damage, pos;
        int an, dn, ap, dp;
        string name, msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

                if (! target || ! me->is_fighting(target))
                        return notify_fail(DAN "只能在战斗中对对手使用。\n");

        lvl = me->query_skill("jiuyin-hamagong", 1);
        lvp = me->query_skill("poison");

        if (lvl < 160)
                return notify_fail("你的蛤蟆功不够娴熟，难以施展" DAN "。\n");

        if (lvp < 180)
                return notify_fail("你对毒技的了解不够，难以施展" DAN "。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力修为不足，难以施展" DAN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的内息不足，难以施展" DAN "。\n");

        // 任务NPC可以直接施展
        if( userp(me) && !objectp(du=query_temp("handing", me)) )
                return notify_fail("你必须拿着(hand)些毒药才能施展" DAN "。\n");

        if (objectp(du) && ! mapp(query("poison",du))) 
                return notify_fail("你手中所拿的" + du->name() + NOR "不"
                                   "是毒药，难以施展" DAN "。\n");

        if( objectp(du) && query("no_shot", du) )
                return notify_fail("将" + du->name() + NOR "弹射出去？似"
                                   "乎不太好吧。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if (objectp(du))
                name = du->name();
        else
                name = NOR + RED "毒丸";

        msg = HIR "$N" HIR "默运内功，施出蛤蟆功绝招「" HIR "弹射毒药"
              HIR "」，将手中" + name + HIR "「嗖」地弹向$n" HIR "。\n" NOR;

        an=query("max_neili", me)+query("neili", me)/4;
        dn=query("max_neili", target)+query("neili", target)/4;

        // 首先判断内力，如果对方内力过高则无效
        if (an * 3 / 5 + random(an) < dn)
        {
                msg += WHT "然而$n" WHT "全然不放在心上，轻轻一抖，已将$N"
                       WHT "射来毒丸打落。\n" NOR;
                me->start_busy(3);
                addn("neili", -150, me);
        } else
        {
                ap = me->query_skill("force") +
                     me->query_skill("poison");

                // 将任务NPC和玩家区分，再计算防御状况
                if (userp(me))
                        dp = target->query_skill("dodge") +
                             target->query_skill("martial-cognize");
                else
                        dp = target->query_skill("dodge") +
                             target->query_skill("parry");

                damage = pos / 2 + random(pos / 2);

                if (ap / 2 + random(ap) > dp)
                {
                        msg += HIR "$n" HIR "一个不慎，毒丸已经射入体内，顿时痛苦不堪。\n" NOR;

                        COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 55, " ");
                             
                        target->affect_by("baituo_poison",
                        ([ "level"    : lvp + random(lvp),
                           "id":query("id", me),
                           "duration" :40 + random(lvp / 20) ]));

                        target->receive_damage("jing", damage / 2, me);
                        target->receive_wound("jing", damage / 3, me);

                        me->start_busy(2);
                        addn("neili", -200, me);
                } else
                {
                        msg += CYN "可是$n" CYN "见势不妙，急忙腾挪身形，终"
                               "于避开了$N" CYN "射来的毒丸。\n" NOR;
                        me->start_busy(3);
                        addn("neili", -100, me);
                }
        }
        message_combatd(msg, me, target);

        // 消耗毒药数量
        if (objectp(du))
        {
                if (du->query_amount())
                {
                        du->add_amount(-1);

                        if (du->query_amount() < 1)
                                destruct(du);
                } else
                        destruct(du);
        }
        return 1;
}
