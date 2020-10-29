// feng.c

#include <ansi.h>
#include <combat.h>

string name() { return HIW "剑气封喉" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill("force") < 240)
                return notify_fail("你的内功的修为不够，难以施展" + name() + "。\n");

        if (me->query_skill("xueshan-jian", 1) < 160)
                return notify_fail("你的雪山剑法修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "xueshan-jian")
                return notify_fail("你没有激发雪山剑法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "只听$N" HIW "一声清啸，手中" + weapon->name() +
              HIW "龙吟不止，迸出万道光华，疾闪而过，无数劲风席卷"
              "$n" HIW "而去！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        damage = damage_power(me, "sword");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "$n" HIR "只感寒风袭体，全身一阵冰"
                                           "凉，已被$N" HIR "剑气所伤。顿时喉咙一"
                                           "甜，喷出一大口鲜血。\n" NOR);
        } else
        {
                addn("neili", -50, me);
                msg += CYN "可是$n" CYN "看破" CYN "$N" CYN
                       "的招数，飞身跃开丈许，终于将这阴寒剑"
                       "气驱于无形。\n"NOR;
        }

        msg = HIW"$N随即长啸一声，手中" + weapon->name() + HIW"疾卷，掀起万朵雪花向前铺天盖地地撒去。\n"
              "在白茫茫的一片中，忽然出现万朵梅花形剑花，穿透雪幕，朝四面八方狂射而出。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "$n" HIR "只觉剑光束束，在自己身上丝丝划过，一时全身剧痛，鲜血飞溅得到处都是。\n" NOR);
        } else
        {
                addn("neili", -50, me);
                msg += CYN "可是$p" CYN "丝毫不为$P"
                       CYN "华丽的剑光所动，稳稳将这一剑架开。\n" NOR;
        }
        me->start_busy(2 + random(2));
        message_combatd(msg, me, target);

        return 1;
}