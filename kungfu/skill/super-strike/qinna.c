// by darken@SJ

inherit F_SSERVER;
#include <ansi.h>

string perform_name(){ return HBBLU"铁掌擒拿"NOR; }
int perform(object me, object target)
{
        string msg;
        if( !target ) target = offensive_target(me);
        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("「铁掌擒拿手」只能对战斗中的对手使用。\n");
        if( (int)me->query_skill("force", 1) < 150 )
                return notify_fail("你的归元吐纳法修为未到，无法使出铁掌擒拿手。\n");
        if( (int)me->query_skill("dodge", 1) < 150 )
                return notify_fail("你的水上漂修为未到，无法使出铁掌擒拿手。\n");
        if( (int)me->query_skill("super-strike", 1) < 150 )
                return notify_fail("你的铁掌修为未到，无法使出铁掌擒拿手。\n");
        if( (int)me->query("jingli") < 1000 )
                return notify_fail("你现在精力太弱，不能出铁掌擒拿手。\n");
        if (target->is_busy())
                return notify_fail("他已经被击中了，不需要再使用铁掌擒拿手。\n");

        me->start_perform(4,"铁掌擒拿手");

        msg = HBBLU"\n$N使出铁掌擒拿手，看准$n的手腕，一把抓去！\n"NOR;
        if (random(me->query_dex()) > target->query_dex() || random(me->query_str()) > target->query_str())
        {
                msg = HIR"\n$N铁掌擒拿手一把抓住$n手腕，往外一扳，$n剧痛下只得停止攻击，采取守势。\n"NOR;
                target->set_temp("lost_attack",3+random(3));
                if (!target->is_busy()) target->start_busy(3);
        }
        else {
                me->start_busy(1);
                target->start_busy(1);
                msg += HIR"$n向$N急攻数招，$N只得回手自救。\n"NOR;
        }
        me->add("jingli",-(200+random(100)));
        message_vision(msg, me, target);
        return 1;
}
