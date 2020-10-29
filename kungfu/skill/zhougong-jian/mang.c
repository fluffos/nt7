// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "剑芒" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        object ob;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("zhougong-jian", 1) < 140)
                return notify_fail("你的周公剑火候太浅，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功修为太浅，难以施展" + name() + "。\n");

        if( query("max_neili", me)<2200 )
                return notify_fail("你的内力修为太浅，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不足，，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        damage = damage_power(me, "sword");

        msg = HIW "$N" HIW "一声清啸，手中" + weapon->name() + HIW "凌"
                  "空划出，剑尖陡然生出半尺吞吐不定的青芒，一道剑气破空"
                  "径直划向$n。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           HIR "$n" HIR "一声惨叫，凌厉的剑气已划"
                                           "过气门，在身上刺出数个血洞，鲜血如泉"
                                           "水般涌出！\n" NOR);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$N"
                       CYN "的企图，斜跃避开。\n" NOR;
        }

        msg += HIW "\n$N" HIW "见$n" HIW "应接不暇，一声冷笑，兵刃挥洒而"
              "出，一记更加凌厉的剑芒由剑尖弹射而出，凌空直射$n" HIW
              "。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "只听“噗嗤”一声，剑气正中$n" HIR
                                           "胸口，留下一个碗口大的血洞！$n" HIR
                                           "哀嚎一声，再也无法站起。\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "强忍全身的痛楚，飞身一跃，避开了$N"
                       CYN "这强大的杀着。\n" NOR;
        }
        me->start_busy(2 + random(2));
        addn("neili", -400, me);
        message_combatd(msg, me, target);
        return 1;
}
