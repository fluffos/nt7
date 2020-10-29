//lian.c 落霞满天
// looo/2001/6/24
#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)

{
        object weapon;
        string msg;

        int i, j, skill;
        skill = (int)(me->query_skill("cuff"));
        j = skill/4;
        i=5+query("tianmo_jieti/times", me);

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail("「落霞满天」只能在战斗中对对手使用。\n");

        if(me->query_skill_mapped("cuff") != "luorishenquan-cuff") 
                return notify_fail("你没有用落日神拳，无法使用「落霞满天」绝招！\n");

        if (me->query_skill_prepared("cuff") != "luorishenquan-cuff")
                return notify_fail("你没有准备使用落日神拳，无法施展「落霞满天」绝招。\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必须空着双手才能使用拳法绝招。\n");

        if( (int)me->query_skill("luorishenquan-cuff", 1) < 220 )
                return notify_fail("你的落日神拳法还不够娴熟，使不出「落霞满天」绝技。\n");

        if( (int)me->query_skill("force") < 300 )
                return notify_fail("你的内功等级还不够，使不出「落霞满天」绝技。\n");

        if( query("max_neili", me)<(me->query_skill("force")+i*j+2000) )
                return notify_fail("你的内力修为需要进一步提高，才能使出「落霞满天」这种超强绝招。\n");

        if( query("neili", me)<(me->query_skill("force")+i*j) )
                return notify_fail("你现在真气太弱，还敢使用「落霞满天」？\n");


        msg = HIM "\n$N" HIM "身形飘飞，双拳急骤击出，四周全是飞舞的拳影，赫然正是『落霞满天』！\n" NOR;

        message_combatd(msg, me, target);

        addn_temp("apply/str", 7, me);
        addn_temp("apply/damage", j, me);
        addn_temp("apply/attack", j, me);

        while (i-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(4);

        target->start_busy(1);

        addn_temp("apply/str", -7, me);
        addn_temp("apply/damage", -j, me);
        addn_temp("apply/attack", -j, me);

        return 1;
}
