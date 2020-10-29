// yitian.c 倚天剑决

#include <ansi.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "倚天剑诀"; }

int perform(object me, object target)
{
        object weapon, ob;
        int extra,i,time;
        string msg;

        i = me->query_skill("yitian-jian", 1) * 5 / 4 + me->query_skill("linji-zhuang", 1);
        i /= 3;
        time = 5;
        if( !target ) target = offensive_target(me);

        if( !me->is_fighting() )
                return notify_fail("「倚天剑决」只能在战斗中使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("「倚天剑决」必须用剑才能使用！\n");

        if (me->query_skill_mapped("sword") != "yitian-jian")
                return notify_fail("你没有激发倚天剑法，怎么使用「倚天剑决」啊？\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内功修为不够！\n");
        if( query("neili", me)<500 )
                return notify_fail("你的真气不够！\n");

        if( (int)me->query_skill("yitian-jian",1) < 120 )
                return notify_fail("你的倚天剑法还不到家，无法使用「倚天剑决」！\n");

        if( !living(target) )
                return notify_fail("对方已经这样了，不需要这么费力吧？！\n");

        msg =HIY "$N" HIY "长啸一声：\n" HIR "武林至尊、宝刀屠龙。号令天下，莫敢不从。倚天不出，谁与争锋? \n"
             HIR "顿时风云变色，" HIR "$N" HIR "手中舞出漫天剑光........ \n" NOR;

        message_combatd(msg, me);
        addn_temp("apply/attack", i, me);
        addn_temp("apply/damage", i*2, me);
        for(int n = 0; n < time; n++)
        {
                msg =  HIC "-----拔云见日!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);
                if (! me->is_fighting(target))
                {
                        addn_temp("apply/attack", -i, me);
                        addn_temp("apply/damage", -i*2, me);
                        addn("neili", -200, me);
                        msg =HIY "$N暗念倚天剑决，身法陡然加快！\n" NOR;
                        message_combatd(msg, me);
                        me->start_busy(1+random(2));
                        return 1;
                }

                if( !living(target) ) break;
                        msg =  BLU "-----星河在天!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                if (! me->is_fighting(target))
                {
                        addn_temp("apply/attack", -i, me);
                        addn_temp("apply/damage", -i*2, me);
                        addn("neili", -200, me);
                        msg =HIY "$N暗念倚天剑决，身法陡然加快！\n" NOR;
                        message_combatd(msg, me);
                        me->start_busy(1+random(2));
                        return 1;
                }
                if( !living(target) ) break;
                msg =  HIY "-----倚天不出!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                if (! me->is_fighting(target))
                {
                        addn_temp("apply/attack", -i, me);
                        addn_temp("apply/damage", -i*2, me);
                        addn("neili", -200, me);
                        msg =HIY "$N暗念倚天剑决，身法陡然加快！\n" NOR;
                        message_combatd(msg, me);
                        me->start_busy(1+random(2));
                        return 1;
                }
                if( !living(target) ) break;
                msg =  HIR "-----谁与争锋!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                if (! me->is_fighting(target))
                {
                        addn_temp("apply/attack", -i, me);
                        addn_temp("apply/damage", -i*2, me);
                        addn("neili", -200, me);
                        msg =HIY "$N暗念倚天剑决，身法陡然加快！\n" NOR;
                        message_combatd(msg, me);
                        me->start_busy(1+random(2));
                        return 1;
                }
                if( !living(target) ) break;
                msg =  HIM "-----号令天下!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);
                break;
        }
        addn_temp("apply/attack", -i, me);
        addn_temp("apply/damage", -i*2, me);
        addn("neili", -200, me);
        msg =HIY "$N暗念倚天剑决，身法陡然加快！\n" NOR;
        message_combatd(msg, me);
        me->start_busy(1+random(2));
        return 1;
}
