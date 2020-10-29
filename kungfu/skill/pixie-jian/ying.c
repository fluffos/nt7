// ying.c 鬼影

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && query("gender", me) != "无性" && !query("special_skill/ghost",me))
                return notify_fail("你的性别与日月内功相斥，无法使用此绝招！\n");  

        if( userp(me) && !query("can_perform/pixie-jian/ying", me) )
                return notify_fail("你还不会使用「鬼影」这一招。\n");

        if (! me->is_fighting(target))
                return notify_fail("「鬼影」只能对战斗中的对手使用。\n");

        skill = me->query_skill("pixie-jian", 1);

        if (skill < 120)
                return notify_fail("你的辟邪剑法修为有限，现在不能使用「鬼影」！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真气不够，无法运用「鬼影」！\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
           query("skill_type", weapon) != "sword" )
                return notify_fail("你只有装备剑才能施展「鬼影」！\n");

        if( me->query_skill_mapped("sword") != "pixie-jian") 
                return notify_fail("你并没有使用辟邪剑法，无法使用此绝招！\n"); 

        if (weapon)
        {
                msg = HIR "\n$N" HIR "冷笑一声，如鬼魅般飘向$n，身法快得不可思议!"
                      HIR "手中的" + weapon->name() + HIR "或点，或刺，或劈，\n刹时间已向$n周身上下连攻数剑!\n\n"
                      HIC "$n根本无法看清剑招的来路，当下方寸大乱" HIC "!\n" NOR; 
       
        }

        message_combatd(msg, me, target);
        count = skill + me->query_skill("kuihua-xinfa", 1);
        if( me->query_skill_mapped("force") != "kuihua-xinfa")
        count /= 2;

        addn_temp("apply/attack", count, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me,target,weapon,TYPE_LINK);
        }
        
        me->start_busy(2 + random(3));
        addn_temp("apply/attack", -count, me);
        
        return 1;
}
