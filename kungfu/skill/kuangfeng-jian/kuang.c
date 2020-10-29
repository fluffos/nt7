// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "天外狂龙"; }

int perform(object me, object target)
{
        string msg;
        int extra, damage, ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);
        if (! target
        ||  ! target->is_character()
        ||  ! me->is_fighting(target))
                return notify_fail("［天外狂龙］只能对战斗中的对手使用。\n");

        if( !weapon=query_temp("weapon", me) )
                return notify_fail("你没装兵器怎么打！\n");

        if( query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的兵器不对！\n");

        if ((int)me->query_skill("kuangfeng-jian", 1) < 100)
                return notify_fail("你的狂风快剑不够熟练，使不出 [ 天外狂龙 ] 。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的内力不够！\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的剑法不够娴熟，使不出 [ 天外狂龙 ] 的绝招！\n");

        extra = me->query_skill("kuangfeng-jian", 1);

        msg = HIY "$N" HIY "剑斜斜刺出，激起股股剑气，拔剑，收剑。在那一瞬间，天地变幻，人影竟似已缩小，\n"
              "但见剑夹杂着风，风里含着剑影！那剑气幻作无数条金黄色的龙铺天盖地袭向$n！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -200, me);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "只觉得脑中轰的一下，"
                                           "身子往后倒飞出去，跌倒在地，不禁“哇”的吐了一口鲜血！n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -100, me);
                msg += CYN "可是$p" CYN "看破了$P" CYN "的狠毒企图，向旁跳开数步，躲开了$P" CYN "的这一波可怕的攻击！\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}