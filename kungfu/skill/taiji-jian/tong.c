// This program is a part of NITAN MudLIB
// tong.c 天地同寿

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "天地同寿"; }

int perform(object me, object target)
{
        string msg;
        object weapon;
        int ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("天地同寿只能对战斗中的对手使用。\n");

        if( me->is_busy() )
                return notify_fail("你现在忙着呢，使不出这一招。\n");

        weapon=query_temp("weapon", me);
        if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("你手中无剑，如何使得天地同寿？\n");

        if( (int)me->query_skill("sword") < 150 )
                return notify_fail("你的太极剑法极不够娴熟，不会使用天地同寿。\n");

        if( (int)me->query_skill("taiji-shengong", 1) < 120 )
                return notify_fail("你的太极神功修为不够，不会使用天地同寿。\n");

        if( me->query_skill_mapped("force") != "taiji-shengong")
                return notify_fail("你所用的内功与太极剑意气路相悖！\n");

        ap=me->query_int()+me->query_str()+query("level", me)*46+
             me->query_dex() + me->query_con();

        if( query("shen", me)>query("shen", target)*3/2 )
                ap *= 2;
        dp=target->query_int()+target->query_str()+query("level", target)*46+
             target->query_dex() + target->query_con();

        msg = HIW "$N" HIW "一声悲啸，背心空门大开，飞撞向$n" HIW "怀中，倒转剑柄向自己小腹直插而下！！！\n" NOR;
        me->want_kill(target);
        me->start_busy(1 + random(2));

        if( ap / 2 + random(ap) > dp )
        {
                msg += HIR "$n" HIR "猝不及防之下，被$N" HIR "撞入怀中，只觉小腹一凉，" NOR + weapon->name() +
                       HIR "已自$N" HIR "后背透体而入！！！\n" NOR;
                message_combatd(msg, me, target);
                target->die(me);
                me->die(target);
                return 1;
        } else
        {
                msg += HIC "$n" HIC "不料$N" HIC "用此招数，手忙脚乱，狼狈万状的躲闪开去，但已吓得手足冰凉，好一阵动弹不得。\n" NOR;
                me->die(target);
                if( !target->is_busy() )
                        target->start_busy(3 + random(3));
        }

        message_combatd(msg, me, target);

        return 1;
}
