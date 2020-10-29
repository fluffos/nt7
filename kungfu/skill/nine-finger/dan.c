// dan.c 九字真言

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
                return notify_fail("「九字真言」只能对战斗中的对手使用。\n");
 
        if(me->query_skill_mapped("finger") != "nine-finger") 
                return notify_fail("你没有用九字真言手印，无法使用「九字真言」绝招！\n");

        if (me->query_skill_prepared("finger") != "nine-finger")
                return notify_fail("你没有准备使用九字真言手印，无法施展「九字真言」绝招。\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必须空着双手才能使用指法绝招。\n");

        if ((int)me->query_skill("nine-finger", 1) < 200)
                return notify_fail("你的九字真言手印不够娴熟，不会使用「九字真言」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你现在内力太弱，不能使用「九字真言」。\n");
                        
        msg = HIM "\n$N" HIM "口中默诵九字真言，忽然招式一缓，身形急退，须臾已在丈许之外。\n"
              "$n" HIM "见$N" HIM "力有不继，正要抢上反击，却见$N" HIM "双手紧扣，拇指微伸，遥指$n" HIM "。 \n"
              "$n" HIM "一时乱了阵脚，不知$N" HIM "所出何招，心头一阵迷惘。\n"
              "忽闻$N" HIM "一声龙吟:\n"
              HIW " 临 兵 斗 者 皆 阵 列 在 前 !\n"
              HIM "喝声中混杂着强劲的" + HIW + to_chinese(me->query_skill_mapped("force")) + HIM "，$n" HIM "不由心神大乱，\n"
              "只感到对方此拳充天塞地，螺旋真气滔滔不绝从四面八方涌来，即使协生双翼，还是避无可避！\n\n" NOR;

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
                               HIM "$N" HIM "竟是置若罔闻，" HIW "螺旋劲气" HIM "仍旧绵绵不绝，$n" HIM "手中" + weapon2->name() + HIM "在真气激荡之下，\n"
                               HIM "化为寸许的二三十截，飞上半空，闪出点点白光！\n" NOR;
                                damage -= damage/3;
                                weapon2->set_name("碎裂的"+query("name", weapon2));
                                weapon2->move(environment(target));
                                set("value", 0, weapon2);
                                set("weapon_prop", 0, weapon2);
                                target->reset_action();
                } else
                        msg += HIM "\n$n" HIM "见$N" HIM "来势凶猛，不敢正面抵挡，侧身进步双掌奋力侧击$N，\n"
                               "$N" HIM "竟是置若罔闻，" HIW "螺旋劲气" HIM "仍旧绵绵不绝，$n" HIM "无可奈何之下，被击个正着！\n" NOR;

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
                               "$N" HIM "被缓得一缓，" HIW "螺旋劲气" HIM "已然落空\n" NOR;
                else
                        msg += HIM "\n$n" HIM "见$N" HIM "来势凶猛，不敢正面抵挡，侧身进步双掌奋力侧击$N，\n"
                               HIM "$N" HIM "被缓得一缓，" HIW "螺旋劲气" MAG "已然落空，但$n" HIM "也被$N" HIM "震得气血翻涌！\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}