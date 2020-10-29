// This program is a part of NITAN MudLIB
// xiang.c 

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i;
        
        if( userp(me) && !query("can_perform/jingang-chu/xiang", me) )
                return notify_fail("你还没有受过高人指点，无法施展镇魂舞。\n");
                 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「镇魂舞」只能对战斗中的对手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "staff" )
                return notify_fail("手中杖还使什么「镇魂舞」！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("staff") < 100)
                return notify_fail("你的基本杖法火候不够！\n");

        if ((int)me->query_skill("jingang-chu", 1) < 100)
                return notify_fail("你的胡金刚镇魂舞杵还不到家，无法使用「镇魂舞」！\n");

        if (me->query_skill_mapped("staff") != "jingang-chu")
                return notify_fail("你没有激发金刚镇魂舞杵，无法使用「镇魂舞」！\n");

        msg = HIW "$N" HIW "施展出镇魂舞杵的精妙招式「镇魂舞」，只见" + weapon->name() +
              HIW "吞吞吐吐，变化莫测，笼罩了$n" HIW "周身要害！\n" NOR;


        message_combatd(msg, me, target);
        
        count = me->query_skill("jingang-chu", 1) / 10;
        
        addn("neili", -150, me);
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));
        return 1;
}

