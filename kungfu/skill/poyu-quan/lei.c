// This program is a part of NITAN MudLIB
// leidong.c 雷动九天

#include <ansi.h>

inherit F_SSERVER;

string name() { return "雷动九天"; }

int perform(object me, object target)
{
        string msg;
        int improve, skill; 
        object weapon=query("weapon", me);
        mapping buff, data;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("雷动九天只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用雷动九天！\n");

        if ((skill = (int)me->query_skill("poyu-quan", 1)) < 80)
                return notify_fail("你的破玉拳不够娴熟，不会使用雷动九天！\n");

        if ((int)me->query_skill("zixia-shengong", 1) < 80)
                return notify_fail("你的紫霞神功不够高，不能用出雷动九天伤敌。\n");

        if (me->query_skill_prepared("cuff") != "poyu-quan"
                || me->query_skill_mapped("cuff") != "poyu-quan")
                return notify_fail("你现在无法使用「雷动九天」进行攻击。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在内力太弱，无法使出雷动九天。\n");

        if( BUFF_D->check_buff(me, "pyq_lei") )
                return notify_fail("你正在使用雷动九天！\n");

        msg = MAG "$N" MAG "使出劈石破玉拳的绝学雷动九天，顿时天空电闪雷鸣！\n" NOR;

        improve=me->query_dex();
        improve+=me->query_str();
        improve /= 15;
        
        data = ([
                "dex": improve,
                "str": improve, 
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "pyq_lei",
                "attr"  : "bless",
                "name"  : "破玉拳·雷动九天",
                "time"  : skill/5,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的雷动九天运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        
        addn("neili", -150, me);
        if (! target->is_busy())
                target->start_busy(random((int)me->query_skill("poyu-quan", 1) / 100 + 2));

        return 1;
}
