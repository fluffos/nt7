#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "修罗剑神" NOR; } 

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        string sexs;
         
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill("lunhui-sword", 1) < 500)
                return notify_fail("你的六道轮回剑修为不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("你没有激发六道轮回剑，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("你没有激发六道轮回剑，难以施展" + name() + "。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        sexs=query("gender", me) == "男性"?"修罗神般威武":"修罗女神般曼妙多姿";
        msg = HIR "$N" HIR "负剑而立，刹那间，剑气环绕，形态飘逸之极，犹如传说中的" + sexs + "。猛然间，$N" HIR 
              "手中" + weapon->name() + HIR "化出一道剑光，但见一道无形剑气奔向$n" HIR "，竟无一丝预兆。\n" NOR;

        ap = attack_power(me, "sword"); 
        dp = defense_power(target, "parry");
        
        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage *= 3;
                addn("neili", -2000, me);
                me->start_busy(2 + random(4));
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 400,
                                           HIR "只听$n" HIR "一声惨叫，$N" HIR +
                                           weapon->name() + HIR "剑光一闪，一道剑气嵌"
                                           "入$p" HIR "体内尺许，带出一蓬血雨。\n"
                                           NOR);
                if (random(3) == 1)
                {
                        target->receive_damage("jing", damage / 40, me);
                        target->receive_wound("jing", damage / 80, me);
                        target->start_busy(3 + random(4));
                        msg = msg + target->name() +  HIM "突然感觉到头晕木眩，看来是受到了修罗剑气的影响。\n" NOR;
                }
        } else
        {
                addn("neili", -1000, me);
                me->start_busy(4);
                msg += CYN "$n" CYN "见$P" CYN "来势汹涌，不敢轻易抵"
                       "挡，连忙飞身腾挪，躲闪开来。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        return 1;
}