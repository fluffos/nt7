// This program is a part of NITAN MudLIB
// qingxin.c 「清心剑」

#include <ansi.h>

inherit F_SSERVER;
string name() { return "清心剑"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int skill;
        mapping buff, data;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「清心剑」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if (skill = (int)me->query_skill("damo-jian", 1) < 200)
                return notify_fail("你的达摩剑法不够娴熟，不会使用「清心剑」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在真气不够，无法使用「清心剑」。\n");

        if (me->query_skill_mapped("sword") != "damo-jian")
                return notify_fail("你没有激发达摩剑法，无法使用「清心剑」。\n");

        if( BUFF_D->check_buff(target, "dmj_qingxin") )
                return notify_fail("对方刚刚才中过达摩清心剑，你不必再用一次了。\n");

        msg = HIM "$N" HIM "将" + weapon->name() + "轻轻一抖，一股"
              "剑气悄然而出，分作数路攻向$n" HIM "！\n" NOR;

        addn("neili", -200, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "结果$p" HIR "觉得浑身一麻，手足软"
                       "软的竟然使不出一点力道！\n" NOR;
                
                data = ([
                        "attack" : -skill/3,
                        "defense": -skill/3,
                ]);
                
                buff = ([
                        "caster":me,
			"target": target,
			"type":"dmj_qingxin",
			"attr":"curse",
			"name":"达摩剑·清心剑",
			"time": skill/5,
                        "buff_data": data,
			"buff_msg": msg,
			"disa_msg": HIR "你觉得力气恢复了一些。\n" NOR,
                ]);                
        } else
        {
                msg += CYN "可是$p" CYN "内力深厚，使得$P" CYN
                       "这一招没有起到任何作用。\n" NOR;
                message_combatd(msg, me, target);
                me->start_busy(3);
        }
        
        return 1;
}
