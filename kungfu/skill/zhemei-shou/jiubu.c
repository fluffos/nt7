// This program is a part of NITAN MudLIB
// jiubu.c 九部式

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "九部式"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;
        int fmsk = me->query_skill("fanlao-huantong", 1);

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「九部式」只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("zhemei-shou", 1) < 120)
                return notify_fail("你的折梅手法不够娴熟，不会使用「九部式」。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功修为不够高，难以运用「九部式」。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在真气不够，不能使用「九部式」。\n");

        if (me->query_skill_mapped("hand") != "zhemei-shou")
                return notify_fail("你没有激发天山折梅手，不能使用「九部式」。\n");

        msg = HIC "$N" HIC "双手虚虚实实的抓向$n"
              HIC "的要害，身法缥缈，手式奇特，令人难以捉摸。\n" NOR;

        ap=attack_power(me,"hand")+me->query_str()*20+fmsk/25;
        dp=defense_power(target,"dodge")+target->query_dex()*20;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");
                damage+= query("jiali", me);
                addn("neili", -100, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60 + fmsk / 10,
                                           HIR "$p" HIR "一个闪避不及，结果被$P"
                                           HIR "抓了个正中，浑身内息不由得一滞，气血翻涌。\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "身手敏捷，巧妙的躲过了$P"
                       HIC "的攻击！\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}