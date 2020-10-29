#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "大江东去" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        int ap, dp, adp;
        string wp, msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        wp = weapon->name();

        if ((int)me->query_skill("xuantie-jian", 1) < 200)
                return notify_fail("你的玄铁剑法不够娴熟，难以施展" + name() + "。\n");

        /*
        if ((int)weapon->query_weight() < 25000)
                return notify_fail("你手中的" + wp + "分量不够，难以施展" + name() + "。\n");
        */

        if( query("neili", me)<800 )
                return notify_fail("你现在的内力不足，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("你没有激发玄铁剑法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "暗自凝神，顿时一股气劲由身后澎湃迸发，接着单"
              "手一振，手中" + wp + HIW "\n随即横空卷出，激得周围尘沙腾起"
              "，所施正是玄铁剑法「" HIG "大江东去" HIW "」。\n"NOR;

        me->start_busy(2);

        ap = attack_power(me, "sword") + me->query_str()*10;
        dp = defense_power(target, "force") + target->query_str()*10;
        
        adp = 110;
        
        if (query("can_perform/surge-force/new", me) && me->query_skill("surge-force", 1) )
	{
		ap += ap / 2;
		adp = 390;
	}
	
        if( query("character", me) == "光明磊落" || query("character", me) == "国土无双" )
                ap += ap / 5;

        if (ap / 2 + random(ap) > dp)
        {
                if (! target->is_busy())
                        target->start_busy(1);
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                addn("neili", -600, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, adp,
                                           HIR "结果$n" HIR "奋力招架，却被$N" HIR
                                           "这一剑震的飞起，口中鲜血狂吐不止！\n" NOR);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$N"
                       CYN "的企图，急忙斜跃避开。\n"NOR;
                addn("neili", -300, me);
        }
        message_combatd(msg, me, target);

        return 1;
}