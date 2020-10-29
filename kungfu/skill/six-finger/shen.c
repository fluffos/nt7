// jingshen.c 六脉惊神

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "六脉惊神"; }

int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int skill, skill2;
        int damage, n;

        int i;
        i = me->query_skill("six-finger", 1) - 50;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「六脉惊神」只能对战斗中的对手使用。\n");

        if (me->query_skill_mapped("finger") != "six-finger")
                return notify_fail("你没有激发六脉神剑，无法施展「六脉惊神」。\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("你没有准备使用六脉神剑，无法施展「六脉惊神」。\n");

        skill = me->query_skill("six-finger", 1);
        skill2 = me->query_skill("sun-finger", 1);
        if (skill < 200)
                return notify_fail("你的六脉神剑修为有限，无法使用「六脉惊神」！\n");

        if (skill2 < 200)
                return notify_fail("你的一阳指修为有限，无法使用「六脉惊神」！\n");

        if (me->query_skill("force") < 400)
                return notify_fail("你的内功火候不够，难以施展「六脉惊神」！\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的内力修为没有达到那个境界，无法运转内力形成「六脉惊神」！\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必须是空手才能施展「六脉惊神」！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，现在无法施展「六脉惊神」！\n");

        msg = HIY "$N" HIY "十指连动，忽伸忽缩，或点或按，空中气流激荡，剑气自"
              HIY "$N" HIY "指中汹涌而出，惊震四方！！\n"
               HIR "六剑连出，剑气回荡，直割得$n眉毛削落，脸面生痛，再也不能前进半分！\n" NOR; 

        message_combatd(msg, me,target);

        damage = skill + skill2;
        if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 ) 
        {
                damage += damage * n * 15 / 100;
                msg = HIM"$N"HIM"运用气脉流转的辅助，使得六脉惊神伤害更强。\n"NOR; 
                message_combatd(msg, me,target);
        }
        addn_temp("apply/attack", i, me);
        addn_temp("apply/unarmed_damage", damage, me);
        {
                msg =  HIC "-------------------------少冲剑 \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_LINK);


                msg =  HIW "-------------------------少泽剑 \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_LINK);


                msg =  HIY "------------------------ 中冲剑 \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_LINK);


                msg =  HIG "-------------------------关冲剑 \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_LINK);


                msg =  HIM "-------------------------商阳剑 \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_LINK);


                msg =  HIR "-------------------------少商剑 \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_LINK);
        }
        addn_temp("apply/attack", -i, me);
        addn_temp("apply/unarmed_damage", -damage, me);
        addn("neili", -800, me);
        me->start_busy(3);
        return 1;
}
