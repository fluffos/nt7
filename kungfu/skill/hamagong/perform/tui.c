// tui.c 推

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "推天式"; }

int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("蛤蟆功「推天式」只能对战斗中的对手使用。\n");

        skill = me->query_skill("hamagong", 1);

        if (skill < 240)
                return notify_fail("你的蛤蟆功修为不够精深，不能使用「推天式」！\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的内力修为不够深厚，无法施展「推天式」！\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的真气不够，无法运用「推天式」！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "蹲在地上，“嗝”的一声大叫，双手弯"
              "与肩齐，平推而出，一股极大的力道如同"
              "排山倒海一般奔向$n" HIY "。\n" NOR;

        ap=attack_power(me, "force");
        dp=defense_power(target,"force")+target->query_skill("sun-finger", 1);

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -400, me);
                me->start_busy(2);
                damage = damage_power(me, "force");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80,
                                           HIR "$n" HIR "奋力低档，但是$P" HIR "的来势何"
                                           "等浩大，$p" HIR "登时觉得气血不畅，“哇”的"
                                           "吐出了一口鲜血。\n" NOR);
        } else
        if (target->query_skill("sun-finger", 1))
        {
                me->start_busy(2);
                addn("neili", -300, me);
                msg += HIG "然而$p" HIG "哈哈一笑，随手一指刺出，正是一"
                       "阳指的精妙招数，轻易的化解了$P" HIG "的攻势。\n" NOR;
        } else
        {
                addn("neili", -200, me);
                msg += CYN "可是$n" CYN "将内力运到双臂上，接下了$P"
                       CYN "这一推之式，只听“蓬”的一声，震得四周"
                       "尘土飞扬。\n" NOR;
                me->start_busy(3);
                target->start_busy(1);
                if( query("neili", target)>200 )
                        addn("neili", -200, target);
                else
                        set("neili", 0, target);
        }
        message_combatd(msg, me, target);

        return 1;
}