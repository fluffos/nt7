// wuqing.c 美女拳-玉女绝情

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "玉女绝情" NOR; }

int perform(object me, object target)
{
        object ob;
        string msg;
        int damage,jiali,married,ap,dp;

        jiali=query("jiali", me);

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("玉女绝情只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须先放下手中的兵器！\n");

        if( query("gender", me) != "女性" )
                return notify_fail("玉女绝情只有女性才能够使用。\n");

        if( (int)me->query_skill("meinv-quan", 1) < 400 )
                return notify_fail("你的美女拳级别不够，不会使用玉女绝情。\n");

        if( (int)me->query_skill("force", 1) < 120 )
                return notify_fail("你的内功还未娴熟，不能用玉女绝情。\n");

        if( query("neili", me)<600 )
                return notify_fail("你现在内力太弱，不能使用玉女绝情。\n");

        if( query("jingli", me)<200 )
                return notify_fail("你现在精力太弱，不能使用玉女绝情。\n");

        msg = HIB "\n\n$N真气催动，带得拳意纵横无情！\n"NOR;
        msg += HIY "\n$N右手支颐，左袖轻轻挥出，长叹一声，脸现寂寥之意，无奈中使出杀招。\n\n"NOR;

        ap=attack_power(me, "unarmed");
        dp=defense_power(target, "force");

        if( mapp(query("family", target)) && query("family/family_name", target) == "全真教" )
                ap += ap/3;

        if( ap/2 + random( ap ) > dp || !living(target) )
        {
                damage = damage_power(me, "unarmed");

                //判断结婚次数和发生性行为的次数
                if( !mapp(query("couple", me)))married=1;
                else married=query("couple/married", me);
                if( mapp(query("sex", me)))married+=query("sex/times", me);
                damage -= (damage/5) * (married - 1);
                if (damage < 10) damage = 10;

                addn("neili", -200, me);
                target->receive_damage("qi", damage,  me);
                target->receive_wound("qi", random(damage*2/3), me);
                target->start_busy(0);

                if ( damage < 1000) {
                        msg += HIR"只听砰的一声，$n被一拳击中小腹，内血翻涌喷口而出。\n"NOR;
                }else if ( damage < 1800) {
                        msg += HIR"只听砰、砰两声，$n左眼发青、右眼发紫，鲜血直流。\n"NOR;
                }else if ( damage < 2600) {
                        msg += HIR"只听砰、砰、砰三声响，$n头部、胸部、腹部同时被重重击中，鲜血狂喷。\n"NOR;
                }else {
                        msg += HIR"只听砰、砰、砰、砰巨响络绎不绝，$n直被打得骨骼碎裂飞了出去。\n"NOR;
                }
                msg += NOR;
                me->start_busy(2+random(2));
        }
        else
        {
                msg += HIG"$n灵光一现，纵身跃起，本能的反应帮$n逃过此劫。\n\n"NOR;
                addn("neili", -100-query("jiali", me), me);
                me->start_busy(2 + random(2));
                message_combatd(msg+"\n", me, target);
                return 1;
        }

        message_combatd(msg+"\n", me, target);
        COMBAT_D->report_status(target);
        return 1;
}
