#include <ansi.h>
#include <combat.h>

#define HUAN "「" HIY "金莲幻生" NOR "」"

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if( userp(me) && !query("can_perform/jinbiao-jue/huan", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你现在手中没有拿着暗器，难以施展" HUAN "。\n");

        if ((skill = me->query_skill("jinbiao-jue", 1)) < 100)
                return notify_fail("你的金镖诀不够娴熟，难以施展" HUAN "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在真气不足，难以施展" HUAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        addn("neili", -80, me);
        weapon->add_amount(-1);

        msg= HIY "忽然间只见$N" HIY "单袖一扬，袖底顿时窜起一道金光，径直向$n"
             HIY "电射而去。\n" NOR;

        me->start_busy(2);
        my_exp=query("combat_exp", me)+skill*skill/10*skill;
        ob_exp=query("combat_exp", target);
        if (random(my_exp) > ob_exp)
        {
                msg += HIR "结果$p" HIR "躲闪不及，被$P" + HIR "那" +
                       query("base_unit", weapon)+weapon->name()+
                       HIR "射中身体，顿时鲜血四处飞溅！\n" NOR;
                target->receive_wound("qi", skill / 3 + random(skill / 3), me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me,target,query("jiali", me)+100);

                p=query("qi", target)*100/query("max_qi", target);

                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "可是$p" CYN "丝毫不乱，身子略倾，闪开了$P"
                       CYN "发出的" + weapon->name() + CYN "。\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}