// honglian.c 火焰刀  红莲火

#include <ansi.h>
inherit F_SSERVER;

string name() { return "红莲火"; }

void remove_effect(object me, int amount);

int perform(object me)
{
        int count, skill;
        mapping buff, data;
        string msg;
        
        skill = me->query_skill("longxiang-gong");

        /*
        if( !me->is_fighting() )
                return notify_fail("「红莲火」只能在战斗中的使用。\n");
        */

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能运用「红莲火」！\n");

        if( BUFF_D->check_buff(me, "atkup") )
                return notify_fail("你正在使用「红莲火」。\n");

        if( (int)me->query_skill("huoyan-dao", 1) < 180 )
                return notify_fail("你的火焰刀不够娴熟，还不能领会「红莲火」之诀窍。\n");

        if ( me->query_skill_mapped("strike") != "huoyan-dao")
                return notify_fail("你必须使用火焰刀来施展「红莲火」。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力修为太弱，使不出「红莲火」。\n");

        if( query("neili", me)<800 )
                return notify_fail("你现在真气不够，使不出「红莲火」。\n");

        if( userp(me) && (int)me->query_skill("longxiang-gong", 1) < 100 )
                return notify_fail("你的龙象般若神功等级不够高，使不出「红莲火」。\n");

        if( me->query_skill_mapped("force") != "longxiang-gong" && me->query_skill_mapped("force") != "xiaowuxiang")
                return notify_fail("你所使内功于火焰刀心法不符，使不出「红莲火」。\n");

        if( userp(me) && (int)me->query_skill("lamaism", 1) < 150 )
                return notify_fail("你对密宗心法的领悟不够，无法使用「红莲火」。\n");

        me->receive_damage("qi", 0);
        msg = RED"\n$N" RED "祭起火焰刀之「红莲火」绝技，精纯的内力呈红色缓缓涌出，于身前三尺之处\n"
                        RED "飘荡无定的真气定在半空，虚无缥缈，不可捉摸！\n"NOR;
        count = skill / 2;

        addn("neili", -300, me);
        addn("jing", -50, me);
        
        data = ([
                "attack" : count,
                "strike" : count/2,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "atkup",
                "attr"  : "bless",
                "name"  : "火焰刀·红莲火",
                "time"  : skill/3,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你身前飘荡无定的火炎隐隐退去。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}
