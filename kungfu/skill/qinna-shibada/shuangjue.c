// shuangjue.c  拳腿双绝

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
              int i, j, z, y;
              i = me->query_skill("zhentian-quan",1);
              j = me->query_skill("chuanyun-tui",1);
              z = me->query_skill("xuantian-wuji",1);
              y = (i+j+z)/4;
              

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("拳腿双绝只能对战斗中的对手使用。\n");

               if( objectp(query_temp("weapon", me)) )
               return notify_fail("你必须空手使用「拳腿双绝」！\n");

        if (me->query_skill_prepared("cuff") != "zhentian-quan"
            || me->query_skill_prepared("leg") != "chuanyun-tui"
            || me->query_skill_mapped("cuff") != "zhentian-quan"
            || me->query_skill_mapped("leg") != "chuanyun-tui")
                return notify_fail("你现在无法使用「拳腿双绝」进行攻击！\n");

        if( (int)me->query_skill("zhentian-quan", 1) < 100 )
                return notify_fail("你的震天拳不够娴熟，无法施展出拳腿双绝。\n");

            if( (int)me->query_skill("strike", 1) < 100 )
                return notify_fail("你的拳法不够娴熟，无法施展出拳腿双绝。\n");

          if( (int)me->query_skill("lag", 1) < 100 )
                return notify_fail("你的腿法不够娴熟，无法施展出拳腿双绝。\n");

             if( (int)me->query_skill("force", 1) < 100 )
                return notify_fail("你的内功不够娴熟，无法施展出拳腿双绝。\n");

        if( (int)me->query_skill("chuanyun-tui", 1) < 150 )
                return notify_fail("你的穿云腿不够娴熟，无法施展出拳腿双绝。\n");
              if( (int)me->query_skill("parry", 1) < 100 )
                return notify_fail("你的招架不够娴熟，无法施展出拳腿双绝。\n");
        if ((int)me->query_skill("xuantian-wuji", 1) < 100)

                return notify_fail("你的玄天无极功火候不够，无法施展出拳腿双绝。\n");
               if( (int)me->query_dex() < 30 )
                           return notify_fail("你的身法欠佳，无法施展出拳腿双绝。\n");
               if( (int)me->query_str() < 30 )
                           return notify_fail("你的体魄不足，无法发挥出拳腿双绝的威力。\n");
               if( (int)me->query_int() < 30 )
                           return notify_fail("你的悟性不够，无法领悟出拳腿双绝。\n");
        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力不够，无法施展出拳腿双绝。\n");
        if( query("neili", me)<1000 )
                return notify_fail("你的真气不够，无法施展出拳腿双绝。\n");

        message_vision(RED "$N一声清啸，拳脚齐施，使出昆仑绝学「拳腿双绝」迅捷无伦地攻向$n！\n"NOR,me, target);
          addn("neili", -400, me);
                 addn_temp("apply/str", y, me);
                 addn_temp("apply/attack", y, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        addn_temp("apply/str", -y, me);
        addn_temp("apply/attack", -y, me);
        me->start_busy(2);
        return 1;
}