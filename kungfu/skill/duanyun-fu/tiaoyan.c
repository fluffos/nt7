// tiaoyan.c 夺命三斧之「挑眼式」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「挑眼式」只能在战斗中对对手使用。\n");

        if ((lvl = me->query_skill("duanyun-fu")) < 60)
                return notify_fail("你的夺命三斧还不到家，不会施展「挑眼式」。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真气不够，无法施展「挑眼式」。\n");

        msg = HIG "$N" HIG "使出夺命三斧之「挑眼式」，斧尖疾挑$n" HIG "双眼。\n" NOR;

        me->start_busy(2);
        if( random(query("combat_exp", me)/100)>query("combat_exp", target)/200 )
        {
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, lvl, 45,
                                           HIR "结果$p" HIR "只觉得眼前一黑，双眼一"
                                           "阵剧痛，血流满面。\n" NOR);
        } else
                msg += HIG "可是$p" HIG "看破了$P" HIG "的企图，急忙躲开了。\n" NOR;

        message_combatd(msg, me, target);

        return 1;
}