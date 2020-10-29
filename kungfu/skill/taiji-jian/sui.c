// This program is a part of NITAN MudLIB
// sui.c 随字诀

#include <ansi.h>

string name() { return "随字诀"; }

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping buff, data;
        object weapon;
        int skill;
        string msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「" + name() + "」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("必须拿剑才能施展「" + name() + "」。\n");

        if ((int)me->query_skill("taiji-jian", 1) < 100)
                return notify_fail("你的太极剑法不够娴熟，不会使用「" + name() + "」。\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 80)
                return notify_fail("你的太极神功火候不够，难以施展「" + name() + "」。\n");

        if( query("neili", me)<query("max_neili", me)/50 )
                return notify_fail("你的内力不够。\n");

        if( BUFF_D->check_buff(me, "parryup") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("taiji-jian");
        msg = HIC "$N使出太极剑法「随」字诀，剑圈逐渐缩小，手中" + weapon->name() +
              HIC "幻出道道光环，将周身护住。\n" NOR;

        data = ([
                "attack": -skill/6,
                "defense": skill*3,
        ]);

        buff = ([
                "caster": me,
                "target": me,
                "type"  : "parryup",
                "attr"  : "bless",
                "name"  : "太极剑法·随字诀",
                "time"  : skill/3,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的随字诀运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        addn("neili", -query("max_neili", me)/50, me);
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}
