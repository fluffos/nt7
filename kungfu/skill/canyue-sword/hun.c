// hun.c 悲欢离合

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

        skill = me->query_skill("canyue-sword", 1);

        if (! me->is_fighting(target))
                return notify_fail("悲欢离合只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("sword") != "canyue-sword") 
                return notify_fail("你没有用残月剑法，无法使用悲欢离合绝招！\n");

        if (skill < 100)
                return notify_fail("你的残月剑法等级不够，练好了再来！\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");
        
        ap = me->query_skill("sword") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIG "$N" HIG "轻轻抖动" + weapon->name() + HIG "，剑花飞扬中依次展现新月、残月、半月、满月等幻影。\n" 
              "$n" HIG "只觉神情恍惚，思绪拥动，悲欢离合百般滋味一一泛显，手脚逐渐缓慢下来。\n" NOR;

        msg += HIY "$N" HIY "乘$n" HIY "思绪混乱，步履蹒跚之际，手中" + weapon->name() + HIY
              "剑芒爆射，星星剑光笼罩$n" HIY "全身，顺势连出数招。\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        msg = YEL "\n$N" YEL "的剑势忽然变慢了，很慢。一剑挥出，似乎永远没有终点。 \n"
              "$n" YEL "终于从先前的狂风暴雨中解脱出来，兀自心有余悸，惊恐不定。\n"
              "不料未及$n" YEL "喘过气来，这笨拙而迟钝的一剑忽然化作了满天月光笼罩下来。 \n\n" NOR; 

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "$n" HIR "始料不及，慌乱之中四处躲闪，刹那间已经身中数剑！\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIW "$n" HIW "大惊之下呆若木鸡，不料这恰好正是残月剑法唯一生门，竟侥幸逃过一劫。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        addn("neili", -damage/3, me);
        return 1;
}
