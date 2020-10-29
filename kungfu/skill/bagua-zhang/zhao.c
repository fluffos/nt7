// zhao.c 八卦掌「罩」字诀
// Create by Haiyan 2002

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int level;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("八卦掌「罩」字诀只能对战斗中的对手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");
                
        if ((level = me->query_skill("bagua-zhang", 1)) < 100)
                return notify_fail("你的八卦掌不够娴熟，不会使用「罩」字诀。\n");

        if( query("neili", me)<60 )
                return notify_fail("你现在真气不够，无法使用「罩」字诀。\n");

        msg = HIG "$N" HIG "脚下步伐加快，使出八卦掌「罩」字诀，双掌"
              "舞出漫天掌影，将$n" HIG "笼罩在当中。\n" NOR;

        addn("neili", -30, me);
        if (random(level) > (int)target->query_skill("parry", 1) / 2)
        {
                msg += HIR "$p" HIR "只觉无数掌影向自己袭来，手忙脚乱，"
                       "呆在当地，不知该如何应对！\n" NOR;
                target->start_busy(level / 30);
        } else
        {
                msg += CYN "然而$p" CYN "看破了$P" CYN "的企图，纵身一跃，"
                       "已跳出了$P" CYN "的掌势。\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}