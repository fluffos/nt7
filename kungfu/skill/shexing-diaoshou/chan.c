// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "缠身决" NOR; }

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        int lvl, damage, itmp;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"只能空手使用。\n");

        if ((int)me->query_skill("xiaoyaoyou", 1) < 150)
                return notify_fail("你的逍遥游不够娴熟，不能使出"+name()+"！\n");

        if ((int)me->query_skill("shexing-diaoshou", 1) < 150)
                return notify_fail("你的蛇行刁手不够娴熟，不能使出"+name()+"！\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 150)
                return notify_fail("你的混天气功等级不够，不能使出"+name()+"！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力太弱，不能使出"+name()+"！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的内力太少了，不能使出"+name()+"！\n");

        /*
        if( !query_temp("gb_huixuan", me) )
                return notify_fail("你没有使出逍遥回旋步，无法使出缠身决！\n");
        */

                /*
        if (target->is_busy())
                return notify_fail("对方正在忙乱中，放心大胆攻击吧！\n");
        */

        if( BUFF_D->check_buff(target, "sxds_diaoshou") && !target->is_busy() )
                return notify_fail(name()+"已经在对方身上发挥过了！\n");

        message_combatd(HIB "\n突然间$N口中发出“嘶嘶”的声音，双手半曲，三指上竖成蛇状，\n"
                        "陪合着潇遥步法，突然欺近$n的身边，令$n大吃一惊。\n" NOR, me, target);
        addn("neili", -200+random(100), me);

                if(! BUFF_D->check_buff(target, "sxds_diaoshou") )
                {
                lvl = ((int)me->query_skill("xiaoyaoyou", 1) +
                   (int)me->query_skill("shexing-diaoshou", 1)) / 2;

                data = ([
                        "defense": -lvl/3,
                    "armor"  : -lvl/3, 
                ]);

                ap = attack_power(me, "hand");
                dp = defense_power(target, "dodge");
        
                itmp = (6000 - (int)me->query_skill("shexing-diaoshou", 1)) / 300;
                if (itmp<5) itmp=5;
                if (itmp>15) itmp=15;
        
                if( ap / 2 + random(ap) > dp )
                {
                        message_combatd(HIB "但见$N的身形有如蛇蝎缠身一般，环在$n的身边，令$n不知所措，\n"
                                        "只觉的仿拂有无形的绳索慢慢的束缚了$n。\n" NOR, me, target);

                    target->start_busy(5);
                }

                buff = ([
                        "caster":me,
                        "target": target,
                        "type":"sxds_diaoshou",
                        "attr":"curse",
                    "name":"蛇形刁手·缠身决",
                        "time":  itmp * 2,
                    "buff_data":data,
                        "buff_msg": "",
                    "disa_msg": HIG "你使出浑身解数，算是挣脱了蛇形刁手的诡异怪招。\n" NOR,
                ]);
                BUFF_D->buffup(buff);
                me->start_busy(1);
                return 1;
        }

        if (target->is_busy())
        {
                ap = attack_power(me, "hand") + me->query_skill("shexing-diaoshou", 1);
                        dp = (defense_power(target, "dodge") + target->query_skill("parry", 1)) / 2;           
                if( ap / 2 + random(ap) > dp )
                {
                        me->start_busy(2);
                        target->stop_busy();
                        damage = damage_power(me, "hand") * 1 / 2;
                        damage+=query("jiali", me)*2/3;
                        
                        msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 40,
                                           HIY "$n" HIY "一不留神，" HIY "小腹中了一记手刀，狂喷数口"HIR"鲜血"HIY"！\n"
                                           ":内伤@?");
                }
                else
                {
                        me->start_busy(3);
                        msg = HIY "$p" HIY "纵身一闪，躲开了$P" HIY "这一招！\n" NOR;
                }
                message_combatd(msg, me, target);
                return 1;
        }

        return 1;
}

