#include <ansi.h>
#include <combat.h>

#define HUI "「" HIR "龍嘯九天" NOR "」"
#define HUIP "「" HIR "亢龙有悔" HIW "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, i;
        object weapon;

        if( userp(me) && !query("can_perform/xianglong-zhang/long", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HUI "只能空手使用。\n");

        if ((int)me->query_skill("force", 1) < 1000)
                return notify_fail("你内功修为不够，难以施展" HUI "。\n");

        if( query("max_neili", me)<10000 )
                return notify_fail("你内力修为不够，难以施展" HUI "。\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 1000)
                return notify_fail("你降龙十八掌火候不够，难以施展" HUI "。\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("你没有激发降龙十八掌，难以施展" HUI "。\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("你没有准备降龙十八掌，难以施展" HUI "。\n");

        if( query("neili", me)<3000 )
                return notify_fail("你现在真气不够，难以施展" HUI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        message_combatd(sort_msg(HIG "\n$N" HIG "凝神聚气，神态淡然，左手虚划，右手回转，聚气于胸前，猛地双"
                         "手推出，刹那间，一招变为数招，同时使出，正是降龙十八掌「" HIR "龍嘯九天" HIG "」，"
                         "气势恢弘，势不可挡 ……\n" NOR), me, target);        

        // 第一掌
        ap=me->query_skill("strike")+query("str", me)*5;
        dp=target->query_skill("dodge")+query("dex", target)*5;
        ap *= 2;
        
        message_combatd(sort_msg(HIW "忽然$N" HIW "身形激进，左手一划，右手呼的一掌"
                     "拍向$n" HIW "，力自掌生之际"
                     "说到便到，以排山倒海之势向$n" HIW "狂涌而去，当真石"
                     "破天惊，威力无比。\n" NOR), me, target);

        if (ap * 3 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap / 2) + me->query_skill("force");
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                          HIR "$P身形一闪，竟已晃至$p跟前，$p躲"
                                          "闪不及，顿被击个正中。\n" NOR);
        } else
        {
                msg = HIC "却见$p气贯双臂，凝神应对，$P掌"
                      "力如泥牛入海，尽数卸去。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第二掌
        ap=me->query_skill("strike")+query("str", me)*5;
        dp=target->query_skill("parry")+query("int", target)*5;
        ap *= 2;

        message_sort(HIW "$N" HIW "一掌既出，身子已然抢到离$n" HIW "三"
                     "四丈之外，后掌推前掌两股掌力道合并，掌力犹如怒潮狂"
                     "涌，势不可当。霎时$p便觉气息窒"
                     "滞，立足不稳。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 2) + me->query_skill("force");
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                          HIR "$p一声惨嚎，被$P这一掌击中胸前，"
                                          "喀嚓喀嚓断了几根肋骨。\n" NOR);
        } else
        {
                msg = HIC "可是$p全力抵挡招架，竟似游刃有"
                      "余，将$P的掌力卸于无形。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第三掌
        ap=me->query_skill("strike")+query("str", me)*5+me->query_skill("force");
        dp=target->query_skill("force")+query("con", target)*5;
        ap *= 2;
        
        message_combatd(sort_msg(HIW "紧跟着$N" HIW "右掌斜挥，前招掌力未消，此招掌"
                     "力又到，竟然又攻出一招，掌夹风势，势如破竹，"
                     "便如一堵无形气墙，向前疾冲而去。$n" HIW "只觉气血翻"
                     "涌，气息沉浊。\n" NOR), me, target);

        if (ap *11 / 20 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                          HIR "结果$p躲闪不及，$P掌劲顿时穿胸而"
                                          "过，顿时口中鲜血狂喷。\n" NOR);
        } else
        {
                msg = HIC "$p眼见来势凶猛，身形疾退，瞬间"
                      "飘出三丈，脱出掌力之外。\n" NOR;
        }              
        message_combatd(msg, me, target);
        
        message_combatd(sort_msg(HIY "$N" HIY "毫无停顿，双掌翻滚，宛如一条神龙攀蜒于九天之上"
                        "。\n" NOR), me, target);
                
        addn_temp("apply/attack", 100000, me);
        addn_temp("apply/damage", 5000, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn_temp("apply/attack", -100000, me);
        addn_temp("apply/damage", -5000, me);
                
        weapon=query_temp("weapon", target);
        if (objectp(weapon) && base_name(environment(me)) != "/d/city/biwu_dating")
        {
                message_combatd(sort_msg(HIG "\n$N" HIG "暴喝一声，全身内劲迸发，气贯右臂奋力外扯，企图将$n"
                                HIW "的" + weapon->name() + HIW "吸入掌中。\n" NOR), me, target);
        
                ap=me->query_skill("strike")+query("str", me)*10;
                dp=target->query_skill("parry")+query("dex", target)*10;
                ap = ap + ap / 2;
                                    
                if (ap / 3 + random(ap) > dp)
                {
                        addn("neili", -300, me);
                        msg = HIR "$n" HIR "只觉周围气流涌动，手中" + weapon->name()
                               + HIR "竟然拿捏不住，向$N" HIR "掌心脱手飞去。\n" NOR;
                        weapon->move(me, 1);
                } else
                {
                        addn("neili", -200, me);
                        msg = CYN "$n" CYN "只觉周围气流涌动，慌忙中连将手中"
                               + weapon->name() + CYN "挥舞得密不透风，使得$N"
                               CYN "无从下手。\n" NOR;
                }
                message_combatd(msg, me, target);
        }
        
        if (random(5) == 1)
        {
                message_combatd(HIG "$N" HIG "生平从未见过如此凌厉恢弘的招式，竟被弄得不知所措。\n" NOR, 
                                target);
                target->start_busy(5 + random(6));
        }

        me->start_busy(3 + random(4));
        addn("neili", -3000, me);
        return 1;
}