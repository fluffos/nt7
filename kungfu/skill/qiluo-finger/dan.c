// dan.c 双绝指

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon,weapon2;
        int damage,i;
        string msg,str;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        
        if (! target || ! me->is_fighting(target))
                return notify_fail("「双绝指」只能对战斗中的对手使用。\n");
 
        if(me->query_skill_mapped("finger") != "qiluo-finger") 
                return notify_fail("你没有用七罗神诀，无法使用「双绝指」绝招！\n");

        if (me->query_skill_prepared("finger") != "qiluo-finger")
                return notify_fail("你没有准备使用七罗神诀，无法施展「双绝指」绝招。\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必须空着双手才能使用指法绝招。\n");

        if ((int)me->query_skill("qiluo-finger", 1) < 200)
                return notify_fail("你的七罗神诀不够娴熟，不会使用「双绝指」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你现在内力太弱，不能使用「双绝指」。\n");
                        
        msg = HIB "\n$N" HIB "口中默读着汽车说明书，忽然招式一缓，车身急退，须臾已在丈许之外。\n"
              HIB "$n" HIB "见$N" HIB "力有不继，正要反击，却见$N" HIB "加大油门反击双手紧扣，双指急转，遥指$n。 \n"
              HIB "$n" HIB "一时乱了阵脚，不知$N" HIB "所出何招，心头一阵迷惘。\n"
              HIW " 万 车 奔 腾 !\n"
              HIB "喝声中混杂着强劲的" HIB + to_chinese(me->query_skill_mapped("force"))+ HIB "，$n" HIB "不由心神大乱，\n"
              HIB "只感到对方此车化身万千，汽车真气滔滔不绝从四面八方涌来，即使协生双翼，还是避无可避！\n\n" NOR;

        ap = me->query_skill("finger") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);
        
        damage = ap*2 + random(ap);
        damage+=query("jiali", me);

        if (living(target))
                dp = target->query_skill("dodge",1) + target->query_skill("parry",1);
        else
                dp = 0;

        dp = dp*3/2;

        weapon2=query_temp("weapon", target);
        
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -damage/2, me);
                if (weapon2)
                {
                        msg += HIM "\n$n" HIM "见$N" HIM "来势凶猛，不敢正面抵挡，手中" + weapon2->name() + HIM "满天幻影，防得水泄不通\n"
                               HIM "$N" HIM "竟是置若罔闻，" HIW "汽车劲气" HIM "仍旧绵绵不绝，$n" HIM "手中" + weapon2->name() + HIM "在真气激荡之下，\n"
                               HIM "化为寸许的二三十截，飞上半空，闪出点点黑光！\n" NOR;
                                damage -= damage/3;
                                weapon2->set_name("碎裂的"+query("name", weapon2));
                                weapon2->move(environment(target));
                                set("value", 0, weapon2);
                                set("weapon_prop", 0, weapon2);
                                target->reset_action();
                } else
                        msg += HIM "\n$n" HIM "见$N" HIM "来势凶猛，不敢正面抵挡，侧身进步双掌奋力侧击$N，\n"
                               "$N" HIM "竟是置若罔闻，" HIW "汽车劲气" HIM "仍旧绵绵不绝，$n" HIM "无可奈何之下，被撞的吐血连连！\n" NOR;

                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else 
        {
                if (weapon2)
                        msg += HIM "\n$n" HIM "见$N" HIM "来势凶猛，不敢正面抵挡，手中" + weapon2->name() + HIM "满天幻影，防得水泄不通\n"
                               "$N" HIM "被缓得一缓，" HIW "汽车劲气" HIM "已然落空\n" NOR;
                else
                        msg += HIM "\n$n" HIM "见$N" HIM "来势凶猛，不敢正面抵挡，侧身进步双掌奋力侧击$N，\n"
                               HIM "$N" HIM "被缓得一缓，" HIW "汽车劲气" MAG "已然落空，但$n" HIM "也被$N" HIM "撞得气血翻涌！\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}