// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define XUAN "「" HIW "太玄激劲" NOR "」"
 
int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XUAN "只能对战斗中的对手使用。\n");
        
        if( me->is_busy() )
                return notify_fail("你正忙着呢！\n");

        if( query("neili", me)<800 )
                return notify_fail("你的真气不够，无法施展" XUAN "！\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的内力修为还不足以使出" XUAN "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功火候不够，难以施展" XUAN "！\n");

        if ((lvl = (int)me->query_skill("taixuan-gong", 1)) < 240)
                return notify_fail("你的太玄功还不够熟练，无法使用" XUAN "！\n");

        // 未学会如何驾御兵器只能激发为拳脚施展 太玄激劲
        if( !query("can_learned/taixuan-gong/enable_weapon", me) )
        {
             weapon=query_temp("weapon", me);
             if (objectp(weapon))
                     return notify_fail("你还没有学会如何利用太玄功驾御兵器，这招只能空手施展！\n");

             if (me->query_skill_mapped("unarmed") != "taixuan-gong"
                 || me->query_skill_prepared("unarmed") != "taixuan-gong")
                       return notify_fail("你没有准备太玄功，无法使用" XUAN "。\n");

        }
        else // 已经学会利用太玄功驾御兵器
        {
             weapon=query_temp("weapon", me);
             // 当没有持武器时判断施展该招需要准备为拳脚
             if (! objectp(weapon))
             {
                    if (me->query_skill_mapped("unarmed") != "taixuan-gong"
                        || me->query_skill_prepared("unarmed") != "taixuan-gong")
                              return notify_fail("你没有准备太玄功，无法使用" XUAN "。\n");
             }          
             // 手持有武器必须为刀或者剑
             else if( objectp(weapon) && query("skill_type", weapon) != "sword"
                       && query("skill_type", weapon) != "blade" )
                              return notify_fail("你使用的武器不对，无法施展" XUAN "。\n");

             if (objectp(weapon) && me->query_skill_mapped("sword") != "taixuan-gong"
                  && query("skill_type", weapon) == "sword" )
                              return notify_fail("你还没有激发太玄功，无法施展" XUAN "。\n");
             
             else if( objectp(weapon) && query("skill_type", weapon) == "blade"
                      && me->query_skill_mapped("blade") != "taixuan-gong")
                              return notify_fail("你还没有激发太玄功，无法施展" XUAN "。\n");                              
                         
        }
        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "\n霎时间$N" HIW "只觉思绪狂涌，当即闭上双眼，再不理睬$n"
              HIW "如何招架，只管施招攻出！此时侠客岛石壁上的千百种招"
              "式，转眼已从$N" HIW "心底传向手足，尽数向$n" HIW "袭去！\n" NOR;

        message_combatd(sort_msg(msg), me, target);
        
        addn("neili", -600, me);
        addn_temp("apply/damage", lvl*2, me);
        addn_temp("apply/unarmed_damage", lvl*2, me);
        addn_temp("apply/attack", lvl/2, me);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                if (! objectp(weapon))
                COMBAT_D->do_attack(me, target, 0, i * 2);
                else
                COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);
        }
        addn_temp("apply/unarmed_damage", -lvl*2, me);
        addn_temp("apply/attack", -lvl/2, me);
        addn_temp("apply/damage", -lvl*2, me);
        me->start_busy(3 + random(5));
        return 1;
}
