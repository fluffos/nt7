// This program is a part of NITAN MudLIB
// xi.c 吸血青蝠

#include <ansi.h>

inherit F_SSERVER;

string name() { return "吸血青蝠"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("hanbing-mianzhang", 1);

        if (! (me->is_fighting(target)))
                return notify_fail("「吸血青蝠」只能对战斗中的对手使用。\n");

        if (objectp(weapon = query_temp("weapon", me)))
                return notify_fail("你使用了武器。\n");

        if (skill < 60)
                return notify_fail("你的「寒冰绵掌」等级不够, 不能使用「吸血青蝠」！\n");

        if (me->query_skill("dodge", 1) < 200)
                return notify_fail("你的轻功基础还没有打好，无法运用「吸血青蝠」！\n");


        msg = HIR "$N" HIR "突然如同蝙蝠一样，倏的欺近$n"
              HIR "的身前，张嘴便向$n" HIR "的咽喉咬去。\n" NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                message_combatd(HIR"结果一下子咬在$n的颈侧，猛吸起来，一股鲜血登时从$N的牙边渗出，阴森可怖。\n\n"NOR,me,target);

                if ( query("combat_exp", me) > random(query("combat_exp", target)*10) )
                {
                        message_vision(HIR"只见$N的腹部微微鼓起，然后放开$n。再看时，$n已经血被吸干，早已气绝。\n"NOR,me,target);
                        me->receive_curing("qi",query("max_qi", target)+100);
                        addn("qi",query("max_qi", target)+100, me);

                        target->die(me);
                }
                else
                {
                        message_vision(HIW"$n拼死挣扎，终于挣脱$N的控制，但受伤极重，鲜血从颈部汩汩流出。\n"NOR,me,target);
                        me->receive_curing("qi",query("max_qi", target)/3);
                        addn("qi",query("max_qi", target)/3, me);
                        target->receive_wound("qi", query("max_qi", target)/3, me);
                        if( !target->is_busy() )
                                target->start_busy(2);
                }

                me->start_busy(1 + random(2));
        } else
        {
                msg = CYN "只见$n" CYN "不慌不忙，轻轻一闪，躲过了$N"
                      CYN "的利齿！\n"NOR;
                addn("neili", -100, me);
                message_combatd(msg, me, target);
                me->start_busy(4);
        }

        return 1;
}
