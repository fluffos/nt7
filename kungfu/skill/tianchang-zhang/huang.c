// This program is a part of NITAN MudLIB
// huang.c 地老天荒

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "地老天荒"; }

int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「地老天荒」只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("必须空手才能施展「地老天荒」。\n");

        if (me->query_skill_mapped("strike") != "tianchang-zhang")
                return notify_fail("你没有激发天长掌法，无法施展「地老天荒」。\n");

        skill = me->query_skill("tianchang-zhang", 1);

        if (skill < 100)
                return notify_fail("你的天长掌法修为有限，不能使用「地老天荒」！\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真气不够，无法运用「地老天荒」！\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "“嚯”的一声震喝，提起掌来，只见掌心一片血红，倏的凌空拍出，"
              HIR "一股热风登时袭向$n" HIR "的胸前大穴。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -120, me);
                me->start_busy(2);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           HIR "$n" HIR "一时间只觉得气血上涌，浑"
                                           "身如遭火焚，气息大乱，不由得吐了一口"
                                           "鲜血。\n" NOR);
        } else
        {
                addn("neili", -50, me);
                msg += HIC "然而$n" HIC "内功深湛，丝毫不为$N"
                       HIC "的掌风所动，若无其事" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}