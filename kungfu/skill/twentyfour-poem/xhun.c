// xhun.c 雄浑

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("twentyfour-poem", 1);

        if (! me->is_fighting(target))
                return notify_fail("雄浑只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("cuff") != "twentyfour-poem") 
                return notify_fail("你没有用诗经二十四品，无法使用「雄浑」绝招！\n");

        if (me->query_skill_prepared("cuff") != "twentyfour-poem")
                return notify_fail("你没有准备使用诗经二十四品，无法施展「雄浑」绝招。\n");

        if (skill < 100)
                return notify_fail("你的诗经二十四品等级不够，练好了再来！\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必须空着双手才能使用掌法绝招。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIC "\n$N" HIC "身形忽转，双拳飘忽不定，真气运转全身，口吐真言，朗朗诵道：\n"
              HIW "大用外腓，真体内充。反虚入浑，积健为雄。具备万物，横绝太空。\n" 
              HIW "荒荒油云，寥寥长风。超以象外，得其环中。持之非强，来之无穷。\n" 
              HIC "真气激荡中，" HIG "诗经二十四品" HIC "至强式" HIY "「雄浑」" HIC "破碎虚空，呼啸而至。\n\n" NOR; 

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIW "\n$N" HIW "万拳归一，缓慢向$n" HIW "击出，却又顷刻而至，端是奇妙！\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIW "$n" HIW "躲闪不急，惨叫一声，已经被重重击中。\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIC "$n" HIC "见势不妙，猛地向后一跃，躲避开来。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}

