#include <ansi.h>
#include <combat.h>

#define KAI "「" HIY "开天辟地" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/pangu-qishi/kai", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KAI "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "hammer" )
                return notify_fail("你使用的武器不对，难以施展" KAI "。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的内功的修为不够，难以施展" KAI "。\n");

        if (me->query_skill("pangu-qishi", 1) < 180)
                return notify_fail("你的盘古七势修为不够，难以施展" KAI "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真气不够，难以施展" KAI "。\n");

        if (me->query_skill_mapped("hammer") != "pangu-qishi")
                return notify_fail("你没有激发盘古七势，难以施展" KAI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = WHT "$N" WHT "一声断喝，手中" + weapon->name() +
              WHT "如山岳巍峙，携着开天辟地之势向$n" WHT "猛劈而下！\n" NOR;

        ap=me->query_skill("hammer")+query("str", me)*10;
        dp=target->query_skill("force")+query("con", target)*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap);
                addn("neili", -500, me);
                me->start_busy(5);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "躲避不及，被$N" HIR "这"
                                           "锤正中胸口，顿时一声闷响，稻草般向后"
                                           "横飞出去。\n" NOR);
        } else
        {
                addn("neili", -300, me);
                me->start_busy(6);
                msg += HIC "可是$n" HIC "真气鼓荡，$N" HIC "雷霆般"
                       "的劲力竟如中败絮，登时被解于无形。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}