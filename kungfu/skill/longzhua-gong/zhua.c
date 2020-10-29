// This program is a part of NITAN MudLIB
// zhua.c 神龙抓

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "神龙抓"; }

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「神龙抓」只能在战斗中对对手使用。\n");

        skill = me->query_skill("longzhua-gong", 1);

        if (skill < 135)
                return notify_fail("你的龙爪功等级不够，不会使用「神龙抓」！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，无法运用「神龙抓」！\n");

        if (me->query_skill_mapped("claw") != "longzhua-gong")
                return notify_fail("你没有激发龙爪功，无法使用「神龙抓」！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "大喝一声，飞身扑至$n" HIY "面前，随即伸手抓向"
              "$p" HIY "的要害！\n" NOR;

        ap = attack_power(me, "claw") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -180, me);
                damage = damage_power(me, "claw");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "$p" HIR "见来势凶猛，难以躲避，只好"
                                           "勉强化解，谁知$P" HIR "的手好像长了眼睛"
                                           "一般，扑哧一下正抓中$p" HIR "的要害，登"
                                           "时鲜血飞溅！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN
                       "的招式，连消带打，全然化解了$P"
                       CYN "的攻势。\n" NOR;
                addn("neili", -60, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
