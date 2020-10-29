// This program is a part of NITAN MudLIB
// you.c 古墓幽居

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "古墓幽居" NOR; }

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg;
        string pmsg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon"))
                return notify_fail("你必须空手才能施展" + name() + "。\n");

        if ((int)me->query_skill("meinv-quan", 1) < 80)
                return notify_fail("你的美女拳法别不够，不会使用" + name() + "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功还未娴熟，不能使用" + name() + "。\n");

        if ((int)me->query("neili") < 180)
                return notify_fail("你现在真气不够，不能使用" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "meinv-quan")
                return notify_fail("你没有激发美女拳法，不能施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "meinv-quan")
                return notify_fail("你没有准备美女拳法，难以施展" + name() + "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "\n$N" HIW "右手支颐，左袖轻轻挥出，长叹一声，使"
              "出古墓派绝学「古墓幽居」，一脸尽现寂寥之意。\n" NOR;

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1+random(2));

                damage = damage_power(me, "unarmed");

                addn("neili", -100, me);

                if (damage < 30)
                        pmsg = HIY "结果$n" HIY "被$N袍"
                               HIY "袖一拂，闷哼一声。\n" NOR;
                else if(damage < 55)
                        pmsg = HIY "结果$n" HIY "被$N"
                               HIY "以袍袖一拂，「腾腾」地退出几步。\n" NOR;
                else if (damage < 80)
                        pmsg = HIR "结果$n" HIR "被$N"
                               HIR "以袍袖一拂，胸口有如受到一记重"
                               "锤，气血为之一窒！\n" NOR;
                else if (damage < 100)
                        pmsg = RED "结果$n" RED "被$N" RED
                               "的袍袖一拂，眼前一黑，浑身气血翻腾，"
                               "竟如身入洪炉一般！\n" NOR;
                else
                        pmsg = HIR "但见$N" HIR "双拳袭来，柔中带刚，迅"
                               "猛无比，其间仿佛蕴藏着无穷的威力，$n" HIR
                               "正迟疑间，却已中拳，闷哼一声，倒"
                               "退几步，一口鲜血喷出。\n" NOR;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45, pmsg);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$P" CYN
                       "的企图，稳如泰山，抬手一架格开了$P"
                       CYN "这一拳。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}