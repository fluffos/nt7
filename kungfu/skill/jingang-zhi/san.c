#include <ansi.h>
#include <combat.h>

string name() { return HIR "一指点三脉" NOR; }

inherit F_SSERVER;

string *xue_name = ({
"劳宫穴", "膻中穴", "曲池穴", "关元穴", "曲骨穴", "中极穴",
"承浆穴", "天突穴", "百会穴", "幽门穴", "章门穴", "大横穴",
"紫宫穴", "冷渊穴", "天井穴", "极泉穴", "清灵穴", "至阳穴", });

int perform(object me, object target)
{
        int damage, lvl;
        string msg, wp;
        object weapon;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("jingang-zhi", 1) < 200)
                return notify_fail("你大力金刚指不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 200)
                return notify_fail("你对经络学了解不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "jingang-zhi")
                return notify_fail("你没有激发大力金刚指，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "jingang-zhi")
                return notify_fail("你没有准备大力金刚指，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        damage = damage_power(me, "finger");
        //lvl = (int)me->query_skill("jingang-zhi", 1);
        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        msg = HIW "突然间";

        msg += "$N" HIW "凝气于指，「" HIR "一指点三脉" HIW "」点出，顿时一股"
               "纯阳的内力直袭$n" HIW "胸口！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
                                           HIR "结果$n" HIR "被$N" HIR "一指点中"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "，全身真气逆流而上，登时呕出一大"
                                           "口鲜血。\n" NOR);

                target->start_busy(ap/90 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "镇定自如，全力化解了$P"
                       CYN "这精妙的一指。\n" NOR;
        }


        me->start_busy(2 + random(3));
        addn("neili", -800, me);
        message_combatd(msg, me, target);

        return 1;
}
