#include <combat.h>
#include  <ansi.h>

#define HUI "「" HIW "毁天" HIR "灭地" NOR "」"

string final1(object me, object target, int damage);
string final2(object me, object target, int damage);

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, lvl;
        object weapon;
         int attack_type;

        if( userp(me) && !query("can_perform/kuihua-mogong/hui", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("kuihua-mogong", 1) < 320)
                return notify_fail("你葵花魔功修为不够，难以施展" HUI "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你内力修为不够，难以施展" HUI "。\n");

        if (me->query_skill_mapped("force") != "kuihua-mogong")
                return notify_fail("你没有激发葵花魔功为内功，无法施展" HUI "。\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "sword" && 
                    query("skill_type", weapon) != "pin" )
                        return notify_fail("你使用的武器不对！\n");

                attack_type = WEAPON_ATTACK;
        } else
        {
                if (me->query_skill_prepared("unarmed") != "kuihua-mogong")
                        return notify_fail("你并没有准备使用葵花魔功，无法施展" HUI "！\n");

                attack_type = UNARMED_ATTACK;
        }

        
        if( query("neili", me)<800 )
                return notify_fail("你现在真气不够，难以施展" HUI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        lvl = me->query_skill("kuihua-mogong", 1);

        message_vision("\n\t\t" + BBLU + HIR "毁    天    " HIW "灭    地\n" NOR, me);

        // 第一式-----毁天
        ap = me->query_skill("force") + me->query_skill("dodge");
        dp=target->query_skill("force")+query("dodge", target);

        message_combatd(sort_msg(HIW "\n忽然间$N" HIW "身形猛转，刹时狂风如潮，遮云蔽"
                     "日，天地为之变色，这正是《葵花宝典》所记载绝学「" HIR "毁天"
                     "式" HIW "」。转眼间$N" HIW "已不见了踪影，只听得一声尖啸，一"
                     "道白光从天而下将$n" HIW "笼罩！" NOR), me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, attack_type, damage, 130,
                                           (: final1, me, target, damage :));

                if( !query("can_perform/kuihua-mogong/hui2", me) )
                {
                       addn("can_perform/kuihua-mogong/hui1", 1, me);
                       if( query("can_perform/kuihua-mogong/hui1", me) >= 200 )
                       {
                            tell_object(me, HIR "你的「毁天式」已经运用得非常熟练了！\n" NOR);
                       }
                }
        } else
        {
                msg = HIC "$p" HIC "眼明身快，纵身向旁一跳，竟躲过这招。。\n" NOR;
        }
        message_combatd(msg, me, target);

        if( query("can_perform/kuihua-mogong/hui2", me) )
        {
        // 第二式-----灭地式        
        message_combatd(sort_msg(HIM "\n紧跟着$N" HIM "身形一晃，已没了踪迹，刹那间，$n" HIM "只觉得地动"
                     "山摇，风起云涌，正犹豫间，$N" HIM "已蹿至$n" HIM "身后，一招"
                     "「" HIR "灭地诀" HIM "」使出 ……\n" NOR), me, target);

        ap = me->query_skill("force") + me->query_skill("dodge");
        dp=target->query_skill("force")+query("dodge", target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, attack_type, damage, 130,
                                          (: final2, me, target, damage :));

                                           
        } else
        {
                msg = HIC "$p" HIC "只觉身后风声呼呼，猛地提气跃开，躲过了这招。\n" NOR;
        }
        message_combatd(msg, me, target);
        }

        me->start_busy(2 + random(3));
        addn("neili", -200-random(300), me);
        return 1;
}

string final1(object me, object target, int damage)
{
        target->receive_wound("qi", damage / 16, me);

        return HIR "$n" HIR "心中大惊，只见$N" HIR "一道"
               "耀眼白光一闪，已晃至自己跟前，躲闪不及，被击"
               "个正中。\n:内伤@?";

}
string final2(object me, object target, int damage)
{
        target->receive_wound("jing", damage / 20, me);
        target->receive_wound("qi", damage / 20, me);
        return  HIR "只听$n" HIR "一声惨嚎，被$N" HIR
                "击中背心，“喀嚓喀嚓”肋骨已震断。\n:内伤@?";
}