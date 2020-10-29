#include <ansi.h>
#include <combat.h>

string name() { return HIW "炼心弹" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object du;
        int lvl, lvp, damage, pos;
        int an, dn, ap, dp;
        string name, fire, msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        lvl = me->query_skill("chousui-zhang", 1);
        lvp = me->query_skill("poison");

        if (lvl < 120)
                return notify_fail("你的抽髓掌不够娴熟，难以施展" + name() + "。\n");

        if (lvp < 180)
                return notify_fail("你对毒技的了解不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("throwing") < 150)
                return notify_fail("你暗器手法火候不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "chousui-zhang")
                return notify_fail("你没有激发抽髓掌，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "chousui-zhang")
                return notify_fail("你没有准备抽髓掌，难以施展" + name() + "。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的内息不足，难以施展" + name() + "。\n");

        // 任务NPC可以直接施展
        if( userp(me) && !objectp(du=query_temp("handing", me)) )
                return notify_fail("你必须拿着(hand)些毒药才能施展" + name() + "。\n");

        if (objectp(du) && ! mapp(query("poison", du))) 
                return notify_fail("你手中所拿的" + du->name() + NOR "不"
                                   "是毒药，难以施展" + name() + "。\n");

        if( objectp(du) && query("no_shot", du) )
                return notify_fail("将" + du->name() + NOR "弹射出去？似"
                                   "乎不太好吧。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        // 根据抽髓掌和毒技的不同，给予不同的信息
        if (lvl >= 200 && lvp >= 270)
        {
                pos = 600 + random(lvp * 4 / 3);
                fire = "一团莹绿色的" HIG "碧焰" HIR;
        } else
        if (lvl >= 180 && lvp >= 240)
        {
                pos = 400 + random(lvp * 3 / 4);
                fire = "一个殷红色的火球";
        } else
        if (lvl >= 150 && lvp >= 210)
        {
                pos = 200 + random(lvp * 2 / 3);
                fire = "数点殷红色的" NOR + RED "火星" HIR;
        } else
        {
                pos = 100 + random(lvp / 2);
                fire = "一点暗红色的" NOR + RED "火星" HIR;
        }

        if (objectp(du))
                name = du->name();
        else
                name = NOR + RED "毒丸";

        msg = HIR "$N" HIR "单掌一抖，施出星宿派绝技「" HIW "炼心弹"
              HIR "」，将手中" + name + HIR "「嗖」的弹射了出去。\n"
              "却见那" + name + HIR "射至中途，竟蓦地爆裂开，化作" +
              fire + "飘然袭向$n" HIR "。\n" NOR;

        an=query("max_neili", me)+query("neili", me)/4;
        dn=query("max_neili", target)+query("neili", target)/4;

        // 首先判断内力，如果对方内力过高则无效
        if (an / 2 + random(an) < dn * 2 / 3)
        {
                msg += WHT "然而$n" WHT "全然不放在心上，轻轻一抖，已将$N"
                       WHT "射来的火焰震灭。\n" NOR;
                me->start_busy(3);
                addn("neili", -150, me);
        } else
        {
                ap = attack_power(me, "strike") +
                     me->query_skill("poison");

                // 将任务NPC和玩家区分，再计算防御状况
                if (userp(me))
                        dp = defense_power(target, "dodge") +
                             target->query_skill("martial-cognize")/2;
                else
                        dp = defense_power(target, "dodge") +
                             target->query_skill("parry")/2;

                damage = damage_power(me, "strike") + pos;
                damage+= query("jiali", me);

                if (ap / 2 + random(ap) > dp)
                {
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 85,
                                                  (: final, me, target, damage :));
                        me->start_busy(2);
                        addn("neili", -200, me);
                } else
                {
                        msg += CYN "可是$n" CYN "见势不妙，急忙腾挪身形，终"
                               "于避开了$N" CYN "射来的火焰。\n" NOR;
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

string final(object me, object target, int damage)
{
        object cloth;
        string name;
        int lvp = me->query_skill("poison");

        if( objectp(cloth=query_temp("armor/cloth", target)) )
        {
                if( query("stable", cloth)<100 )
                {
                        addn("consistence", -1-random(10), cloth);

                        if( query("consistence", cloth)<0 )
                                set("consistence", 0, cloth);
                }
                name = cloth->name();
        } else
        if( objectp(cloth=query_temp("armor/armor", target)) )
        {
                if( query("stable", cloth)<100 )
                {
                        addn("consistence", -1-random(10), cloth);

                        if( query("consistence", cloth)<0 )
                                set("consistence", 0, cloth);
                }
                name = cloth->name();
        } else
                name = "肌肤";

        target->affect_by("fire_poison",
                ([ "level"    : lvp * 2 + random(lvp * 3),
                   "id":query("id", me),
                   "duration" : 6 + random(lvp / 30) ]));

        target->receive_damage("jing", damage, me);
        target->receive_wound("jing", damage * 2 / 3, me);
        if( !target->is_busy() )
                target->start_busy(1);

        return  HIR "$n" HIR "一个不慎，火星顿时溅到" + name +
                HIR "之上，大势燃烧起来，皮肉烧得嗤嗤作响。\n" NOR;
}
