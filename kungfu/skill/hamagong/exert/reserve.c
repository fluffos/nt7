// reserve.c 蛤蟆功经脉倒转

#include <ansi.h>

inherit F_CLEAN_UP;

void show_effect(object me, int a_amount);

int exert(object me, object target)
{
        object weapon;
        int skill;
        string msg;
        int delta;
        int n;

        if ((int)me->query_skill("hamagong", 1) < 120)
                return notify_fail("你的蛤蟆功不够娴熟，不会经脉倒转。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不够。\n");

        if( query_temp("reverse", me) )
                return notify_fail("你已经倒转经脉了。\n");

        skill = me->query_skill("hamagong", 1);
        msg = HIB "$N" HIB "忽地双手撑地倒立，逆运经脉，顿时"
              "内息暗生，防御力大增。\n" NOR;
        message_combatd(msg, me);

        delta = ABILITY_D->check_ability(me, "powerup-hmg-reserve");
        n = skill/4;
        n = n + n * delta/100;

        addn_temp("apply/defense", n, me);
        addn_temp("apply/armor", n*2, me);
        addn_temp("apply/dispel_poison", n*2+30, me);
        addn_temp("apply/reduce_poison", 10, me);//提高10%的抗毒
        set_temp("reverse", n, me);

        addn("neili", -100, me);
        if (me->is_fighting())
                me->start_busy(2);

        me->start_call_out((: call_other, __FILE__, "show_effect", me, n :), 10);
        return 1;
}

void show_effect(object me, int n)
{
        if( !query_temp("reverse", me) )
               return ;

        n=query_temp("reverse", me);

        if( query("neili", me)<200 )
        {
              write(HIG "你逆运经脉，内力耗尽，猛然间气血上涌，你感觉自己内力受到了损伤。\n" NOR);
              addn("max_neili", -1, me);
              set("neili", 0, me);
              delete_temp("hmg_dzjm", me);
              addn_temp("apply/defense", -n, me);
              addn_temp("apply/armor", -n*2, me);
              addn_temp("apply/dispel_poison", -1*(n*2+30), me);
              addn_temp("apply/reduce_poison", -10, me);

              return;
        }

        addn("neili", -200, me);

        me->start_call_out((: call_other, __FILE__, "show_effect", me, n :), 10);

        return;
}
