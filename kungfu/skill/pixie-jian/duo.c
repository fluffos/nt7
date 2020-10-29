#include <ansi.h>
#include <combat.h>

string name() { return HIR "鬼影夺目" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int lvl, ap, dp;
        int avoid,add,time,fmsk;
        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        weapon=query_temp("weapon", me);

        if( weapon && query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "pin" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("pixie-jian", 1) < 100)
                return notify_fail("你的辟邪剑法不够娴熟，难以施展" + name() + "。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (weapon && me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("你没有准备使用辟邪剑法，难以施展" + name() + "。\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "pixie-jian")
                return notify_fail("你没有准备使用辟邪剑法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if( query_temp("block_msg/all", target) )
                return notify_fail("对方现在什么也看不见，放胆攻击吧。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
        {
                msg = HIR "$N" HIR "一声阴笑，揉身而上，左手两指并拢，手臂"
                      "暴长，迅捷异常分刺$n" HIR "的双目！\n" NOR;
        } else
        {
                msg = HIR "$N" HIR "一声阴笑，揉身而上，手中" + weapon->name() +
                      HIR "一振，剑尖一点暴长，分刺$n" HIR "左右双目！\n" NOR;
        }

        ap = attack_power(me, "sword") +
             me->query_skill("dodge");

        dp = defense_power(target, "parry") +
             target->query_skill("dodge");

        if (ap / 2 + random(ap*2) > dp)
        {
                
                avoid = target->query_all_buff("avoid_blind");
                if(avoid > 90 ) avoid = 90;
                add = me->query_all_buff("add_blind");
                if(add > 90 ) add = 90;
                time = me->query_skill("pixie-jian", 1) /100;
                if( time > 140 ) time = 140;                
                time = time + add - avoid;
                
                if( random(100) < avoid)
                time = 0;
                fmsk = me->query_skill("richu-dongfang", 1);
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                damage+= me->query_all_buff("damage");
                damage+= damage / 300 * me->query_dex();
                
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100+fmsk/10,
                                          (: final, me, target, time :));
                me->start_busy(1+random(2));
                target->set_weak(5);
                addn("neili", -80, me);
                message_combatd(msg, me, target);

        } else
        {
                msg += CYN "$n" CYN "情急智生，抬手也向$N"
                       CYN "的右眼刺去，迫得$P" CYN "回剑跃开。\n" NOR;
                me->start_busy(3);
                addn("neili", -50, me);
                message_combatd(msg, me, target);
        }
        return 1;
}

string final(object me, object target, int time)
{   
    if( time > 0)
    {   
        set_temp("block_msg/all", 1, target);
        target->start_call_out((: call_other, __FILE__, "cimu_end", me, target :), time);
        return HIR "$n" HIR "只觉双目一阵剧痛，眼前一黑，就什么"
               "也看不见了，顿时长声痛极而呼。\n" NOR;
    }
        return HIC"$n一声惨叫，满脸布满了鲜血！\n"NOR;
}

void cimu_end(object me, object target)
{
        if (! objectp(target)) return;
        if( target && query_temp("block_msg/all", target) )
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "抹了抹流着的"
                                        HIR "鲜血" HIC "，终于能看"
                                        "见了。\n" NOR, target);

                        tell_object(target, HIR "你终于抹掉了眼前的"
                                            "鲜血，能看见了。\n" NOR);
                        set_temp("block_msg/all", 0, target);
                }
        }
        return;
}

