#include <ansi.h>
#include <combat.h>

string name() { return HIY "狂风绝技" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("xuanfeng-tui", 1) < 100)
                return notify_fail("你旋风扫叶腿不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("xuanfeng-tui", 1) < 100)
                return notify_fail("你的旋风扫叶腿不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "xuanfeng-tui")
                return notify_fail("你没有激发旋风扫叶腿，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "xuanfeng-tui")
                return notify_fail("你没有准备旋风扫叶腿，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "使出桃花岛狂风绝技，身法飘忽不定，足带风尘，掌携"
              "万钧，有若天仙！\n" NOR;
        message_combatd(msg, me);
        addn("neili", -100, me);

        count = me->query_skill("bibo-shengong", 1) / 2 + me->query_skill("xuanfeng-tui", 1);
        count /= 4;
        addn_temp("apply/attack", count, me);

        msg = YEL  "\n$N" YEL"聚力于左掌，右腿一脚跟着踢出！\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = HIM  "人影中，" HIM "$N" HIM "翻身而起，左掌大力得挥向$n！\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = YEL "\n$N" YEL "见" YEL "$n" YEL "门户大开，暗运内力，双腿连环踢向" YEL "$n！\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = HIM  "$N" HIM "越战越勇，周围骤起一阵旋风，使得" HIM "$n" CYN "看不清方向！\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = YEL "\n$N" YEL "如星光乍现，右掌略带悠然之色轻拍" YEL "$n！\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = HIM "$N" HIM "长啸一声，面如赤发，忽然转到" HIM "$n" HIM"身后，反手又是一掌！\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        addn("neili", -100, me);
        me->start_busy(1 + random(2));
        addn_temp("apply/attack", -count, me);
        return 1;
}