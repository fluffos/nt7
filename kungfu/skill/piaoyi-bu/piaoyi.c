// piaoyi.c 飘逸步法 灵燕飘逸

#include <ansi.h>
#include <combat.h> 

#define PIAOYI HIG "「灵燕飘逸」" NOR 

inherit F_SSERVER;

void remove_effect(object me, int aamount, int damount);

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int d_count, count, qi, maxqi, skill;

        if( query_temp("piaoyi", me) )
                return notify_fail("你已经在运功中了。\n");

        if ( userp(me) 
         && me->query_skill("piaoyi-bu", 1) < 150
          && !query("can_perform/piaoyi-bu/piaoyi", me) )
                return notify_fail( "你所使用的外功中没有这样的功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail( PIAOYI + "只能对战斗中的对手使用。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，无法施展" + PIAOYI + "！\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功修为不够，不能使用" + PIAOYI + "！\n");

        if ((int)me->query_skill("dodge") < 150)
                return notify_fail("你的基本轻功还不到家，无法使用" + PIAOYI + "！\n");

        if (me->query_skill_mapped("dodge") != "piaoyi-bu") 
                return notify_fail("你没有激发飘逸步法，无法使用" + PIAOYI + "！\n");

        msg = HIG "$N" HIG "催动自己的真力运劲于双腿，使出飘逸步法的绝技" + 
              PIAOYI + HIG "，身形顿时如灵燕一般！\n" NOR;
        
        qi=query("qi", me);
        maxqi=query("max_qi", me);
        skill = (int) (me->query_skill("piaoyi-bu", 1) / 3);
        count = (int)me->query_skill("dodge",1) / 4;
        d_count = (int)me->query_skill("parry",1) / 2;

        if (qi > (maxqi * 0.4))
        {       
                message_combatd(msg, me, target);
                
                addn_temp("apply/dodge", count*2, me);
                addn_temp("apply/parry", -d_count, me);
                set_temp("piaoyi", 1, me);
                me->start_call_out((: call_other, __FILE__, "remove_effect", me, count * 2, d_count :), skill);
                addn("neili", -500, me);
        } else
        {
                msg = HIR "$N" HIR "全力催动真力，试图将自己的身行移动提高到极限"
                      ", 双腿骨骼一阵爆响！\n" NOR;
                msg = HIR "$N" HIR "发现自己催动的内力将双腿的经脉尽数震断, 再也站立不住, 一头栽倒在地！\n" NOR;
                message_combatd(msg, me, target);
                set("neili", 0, me);
                addn("max_neili", -10, me);

                me->unconcious();
        }
        return 1;
}

void remove_effect(object me, int aamount, int damount)
{
        if( query_temp("piaoyi", me) )
        {
                addn_temp("apply/dodge", -aamount, me);
                addn_temp("apply/parry", damount, me);
                delete_temp("piaoyi", me);
                tell_object(me, HIG "你的" + PIAOYI + HIG "运功完毕，双腿一阵酸麻。\n");
        }
}