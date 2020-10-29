

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("你只能对战斗中的对手使用「乱影剑」。\n");

        if( query_temp("myj_luan_cd", me) && time()-query_temp("myj_luan_cd", me) < 1 )
                return notify_fail("你上一个动作还没有完成，不能施用外功。\n");

        if (! objectp(weapon = query_temp("weapon",me)) ||
            (string)query("skill_type",weapon) != "sword")
                return notify_fail("你使用的武器不对！\n");
                
        if (me->query_skill_mapped("sword") != "meiying-jian")
                return notify_fail("你没有激发魅影剑法，无法施展。\n"); 

        if ((int)me->query_skill("meiying-jian", 1) < 200)
                return notify_fail("你目前功力还使不出「乱影剑」。\n");

        if ((int)query("neili",me) < 300)
                return notify_fail("你的内力不够。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

             set_temp("myj_luan_cd",time(),me);
        addn("neili", -200,me);
        msg = HIM "\n$N" HIM "露出诡异的笑容，忽然身法陡然加快，有如完全鬼影般旋转，"
              "手中$N" HIM "乱影般激射而出，$n" HIW "只觉魅影围绕，窒息之极！\n" NOR;

        if (random(10) < 2)
        {
                if (random(10) < 7)me->start_busy(1);
                else
                {
                        me->start_busy(2);
                }               
        }
        
        ap = me->query_skill("dodge") + me->query_skill("force");
        dp = target->query_skill("dodge") + target->query_skill("force");
        
        if (ap * 3 / 4 + random(ap) > dp)
        {
                if (random(3) == 1)target->start_busy(2);
                damage = ap * 2 + random(ap);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100, 
                                           HIR "只见$n" HIR "已被$N" HIR
                                           "刺得体无完肤，血如箭般由全身喷射而出！\n" NOR);
        } else
        {
                msg += HIC "可是$p" HIC "急忙抽身躲开，使$P"
                       HIC "这招没有得逞。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        return 1;
}

