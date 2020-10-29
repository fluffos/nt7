// zhua.c 九阴白骨爪 - 九阴神抓

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "九阴神爪" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        string pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用九阴神抓！\n");

        if ((int)me->query_skill("jiuyin-baiguzhao", 1) < 120)
                return notify_fail("你的九阴白骨爪还不够娴熟，不能使用"+name()+"。\n");

        if (me->query_skill_prepared("claw") != "jiuyin-baiguzhao")
                return notify_fail("你没有准备九阴白骨爪，无法使用"+name()+"。\n");

        if( query("neili", me)<240 )
                return notify_fail("你现在内力太弱，不能使用九阴神抓。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "冷笑一声，眼露凶光，右手成爪，三盘两旋虚虚"
              "实实的向$n" HIR "的头顶抓了下来。\n" NOR;

        addn("neili", -50, me);

        ap = attack_power(me, "claw");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -180, me);
                damage = 0;

                if( query("max_neili", me)<query("max_neili", target)*4/5 &&
                    me->query_skill("force") < target->query_skill("force"))
                        msg += HIY "“啪”的一声$N" HIY "正抓在$n" HIY "的天灵盖上，"
                               "结果震得“哇哇”怪叫了两声！\n" NOR;
                else
                if( !playerp(target) && query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIY "“扑哧”一声，$N" HIY "五指正插入$n" HIY "的天灵"
                               "盖，$n" HIY "一声惨叫，软绵绵的瘫了下去。\n" NOR;
                        damage = -1;
                } else
                {
                        if (!target->is_busy())
                        target->start_busy(1 + random(3));

                        damage = damage_power(me, "claw");

                        if( arrayp(limbs=query("limbs", target)) )
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "要害";
                        pmsg = HIC "$n连忙腾挪躲闪，然而“扑哧”一声，$N"
                               HIC "五指正插入$n" HIC "的" + limb + "，$n"
                               HIC "一声惨叫，血射五步。\n" NOR;
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 95, pmsg);
                }
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企图，身形急动，躲开了这一抓。\n" NOR;
        }

        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);
        me->start_busy(2);
        return 1;
}
