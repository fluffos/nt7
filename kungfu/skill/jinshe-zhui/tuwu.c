// This program is a part of NITAN MudLIB
// tuwu.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, ap, dp;
        int damage;
        string msg;
        object weapon;
        mapping buff;

        if( !target) target = offensive_target(me);
        if( !target || ! me->is_fighting(target))
                return notify_fail("金蛇吐雾只能在战斗中使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            // (string)weapon->query("id") != "jinshe zhui" ||
            weapon->query_amount() < 1)
                // return notify_fail("你手里没拿金蛇锥，不能使用绝招！\n");
                return notify_fail("你手里没拿金蛇锥或其他暗器，不能使用绝招！\n");

        if( (skill = me->query_skill("jinshe-zhui", 1)) < 100 )
                return notify_fail("你的金蛇锥法不够娴熟，不会使用金蛇吐雾。\n");

        if( query("neili", me)<300 )
                return notify_fail("你内力不够了。\n");

        if( BUFF_D->check_buff(target, "jinshezhui_tuwu") )
                return notify_fail("对方已经这样了，你就不必了吧。\n");

        weapon->add_amount(-1);

        msg = HIY "$N" HIY "一声轻啸，身形微动，手中金蛇锥竟然向上飞"
              "起绕了个圈，随而迅速袭向$n" HIY "的面前。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
             
        if( ap / 2 + random(ap) > dp )
        {
                addn("neili", -200, me);
                damage = damage_power(me, "strike");
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage / 3, me);
        
                msg += HIM "只听一阵狂风扫叶般的声响中，$N" HIM "手中的"
                       "金蛇锥闪出夺目的光芒，闪耀得$n" HIM "眼冒金花，"
                       "\n除了眼前一重重的雾气外，$n" HIM
                       "啥也看不见了！\n" NOR;
                message_combatd(msg, me, target);
                set_temp("jinshe/tuwu", 1, target);
                set_temp("block_msg/all", 1, target);
                buff = ([
                        "caster":me,
	                "target":target,
	                "type":"jinshezhui_tuwu",
	                "attr": "curse",
	                "name":"金蛇锥法·金蛇吐雾",
	                "time":skill/100,
	                "buff_msg":"",
	                "disa_msg" :"$N抹了抹满脸的" HIR "鲜血" NOR "，终于睁开了眼。\n",
	                "disa_type":1,
                        "block_msg":"all",
                ]);
                BUFF_D->buffup(buff);
        } else
        {
                msg += CYN "$n" CYN "心中暗暗一惊，急忙后"
                       "退，闪开了这枚金蛇锥。\n" NOR;
                message_combatd(msg, me, target);
        }
        
        me->reset_action();
        me->start_busy(1);
        return 1;
}
