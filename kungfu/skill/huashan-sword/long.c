// This program is a part of NITAN MudLIB
// feilong.c 华山剑法「天外飞龙」
// written by Lonely@nt7

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "天外飞龙" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「天外飞龙」只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("不拿剑怎么使用「天外飞龙」？\n");

        if( (int)me->query_skill("huashan-sword", 1) < 150 )
                return notify_fail("你华山剑法不够娴熟，使不出「天外飞龙」。\n");

        if( (int)me->query_skill("force") < 150 )
                return notify_fail("你内功火候不够，使不出「天外飞龙」。\n");

        if( query("neili", me)<2000 )
                return notify_fail(HIC"你现在真气不够，无法将「天外飞龙」使完！\n"NOR);

        if( me->query_skill_mapped("sword") != "huashan-sword" )
                return notify_fail("你没有激发华山剑法，无法使用「天外飞龙」。\n");
        
        msg = HIC "$N" HIC "一声长啸，急运内力，勒手仗剑，猛地向$n" HIC "掷出，霎那间风云变色！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        
        if( ap / 2 + random(ap) > dp )
        {
                damage = -1;
                msg += HIR "只见一道银色闪电划破长空，正在$n" HIR "愣神间，"+query("name", weapon)+HIR "已经穿胸而入，将$n" HIR "狠狠钉在了地上！\n" NOR;
        } else
        if( ap > dp / 3 * 2 )
        {
                damage = damage_power(me, "sword") * 3;
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIC "$n" HIC "见状大惊失色，急忙侧让躲避，谁知"+query("name", weapon)+
                                           HIC"来势太快，只见一道银光划过，$n" HIC "腰腹鲜血汹涌而出！\n" NOR);
                addn("neili", -2000, me);
        } else
        {
                damage = 0;
                msg += CYN "然而$n" CYN "轻轻一笑，侧身伸指，正弹"
                       "在$N" CYN "的剑脊上，剑斜飞落地。\n" NOR;
        }
        
        addn("neili", -2000, me);
        me->start_busy(3);
        if( !weapon->is_item_make() && !query("bind_owner", weapon) )
                weapon->move(environment(me));
        message_combatd(msg, me, target);
        if( damage == -1 ) target->die(me);
                
        return 1;
}
