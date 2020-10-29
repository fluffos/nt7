#include <ansi.h>
#include <combat.h>

#define ZHE "「" HIG "只手遮天" NOR "」"

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

string final(object me, object target, int lvl);

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl, p;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHE "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(ZHE "只能空手施展。\n");

        if ((int)me->query_skill("xuanming-shengong", 1) < 150)
                return notify_fail("你的玄冥神功火候不够，无法施展" ZHE "。\n");

        if ((int)me->query_skill("xuanming-zhang", 1) < 150)
                return notify_fail("你的玄冥神掌不够熟练，无法施展" ZHE "。\n");

        if (me->query_skill_mapped("force") != "xuanming-shengong")
                return notify_fail("你没有激发玄冥神功为内功，无法施展" ZHE "。\n");

        if (me->query_skill_prepared("strike") != "xuanming-zhang")
                return notify_fail("你没有准备玄冥神掌，无法施展" ZHE "。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力修为不足，无法施展" ZHE "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，无法施展" ZHE "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "\n$N" HIW "运起玄冥神功，全身浮现出一层紫气，猛然间双掌翻腾不息，施"
                  "展出绝招「" HIG "只手遮天" HIW "」，携带着万古至毒至寒之气的掌劲"
                  "攻向$n" HIW "！\n"NOR;  

        lvl = me->query_skill("xuanming-zhang", 1);

        ap = attack_power(me, "strike") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        me->start_busy(4);

        if (ap / 2 + random(ap) > dp)
        { 
                damage = damage_power(me, "strike");
                addn("neili", -300, me);
     
                // 玄冥寒毒反噬
                if( query("max_neili", target)*3/5>query("max_neili", me) )
                {
                        message_sort(msg, me, target);
                        message_sort(HIM "$N" HIM "一掌打在$n" HIM "身上，猛然间气血翻腾，一股阴寒之气竟"
                                     "反噬回来，$N" HIM "抵御不住，寒毒侵入体内。$N" HIM "闷哼一声，一"
                                     "口淤血吐出，脸色顿时发紫。" NOR, me, target);

                        me->receive_wound("qi",damage+query("jiali", me)+random(query("jiali", me)/2));

                        p=query("qi", me)*100/query("max_qi", me);
                        msg = "( $N" + eff_status_msg(p) + " )\n\n";
                        message_vision(msg, me, target);

                        me->affect_by("xuanming_poison",
                                      (["level":query("jiali", me)+random(query("jiali", me)),
                                         "id":query("id", me),
                                         "duration" : lvl / 40 + random(lvl / 20) ]));

                        return 1;
                        
                } 

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                          (: final, me, target, lvl :));
                                           
        } else
        {
                msg += HIY "$n" HIY "看见$N" HIY "来势汹涌，急忙提气跃开。\n" NOR;
                addn("neili", -180, me);
        }
        message_sort(msg, me, target);

        return 1;
}

string final(object me, object target, int lvl)
{
        target->affect_by("xuanming_poison",
                         (["level":query("jiali", me)*3,
                            "id":query("id", me),
                            "duration" : lvl / 40 + random(lvl / 20) ]));

        return HIR "$n" HIR "只见眼前紫影晃动，突然间胸口一震，已知大势"
               "不妙，只感胸口处一股寒气升起，尽损三焦六脉。\n" NOR;
}
