// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define HUAN "「" HIR "我必还之" NOR "」"

inherit F_SSERVER;

int can_not_hubo(){ return 1; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int per;

        if( userp(me) && !query("can_perform/xuedao-dafa/huan", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "只能对战斗中的对手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，难以施展" HUAN "。\n");

        if ((int)me->query_skill("force") < 1200)
                return notify_fail("你的内功火候不够，难以施展" HUAN "。\n");

        if ((int)me->query_skill("xuedao-dafa", 1) < 1000)
                return notify_fail("你的血刀大法还不到家，难以施展" HUAN "。\n");

        if (me->query_skill_mapped("force") != "xuedao-dafa")
                return notify_fail("你没有激发血刀大法为内功，难以施展" HUAN "。\n");

        if (me->query_skill_mapped("blade") != "xuedao-dafa")
                return notify_fail("你没有激发血刀大法为刀法，难以施展" HUAN "。\n");

        if( query("qi", me)<100 )
                return notify_fail("你目前气血翻滚，难以施展" HUAN "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你目前真气不足，难以施展" HUAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        msg = HIR "$N" HIR "手中" + weapon->name() + "直指$n" HIR"，口中喝骂道：「洒家什么都吃就是不知亏！人若伤我！我必还之！」\n"
              HIR "只见" + weapon->name() + "泛出浓烈血光、腥味刺鼻，映的四周直若浓血地狱。\n";
              
        if (ap / 2 + random(ap) > dp)
        {
                per=query("eff_qi", me)*100/query("max_qi", me);
                if (per > 60)
                        damage = damage_power(me, "blade");
                else
                if (per < 20)
                        damage = -1;
                else
                        damage=query("max_qi", target)*per/100;
                          
                addn("neili", -150, me);
                me->start_busy(2);
                
                if (damage > 0)
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                           HIR "在$n" HIR "眼中，" + weapon->name() + "的刀尖越来越大、压的自己几乎透不过气，"
                                           HIR "直至猛然一呕血，却发现" + weapon->name() + "已经在自己身上留下狰狞的轨迹。\n" NOR);
                else
                {
                        msg += HIR "在$n" HIR "眼中，" + weapon->name() + "的刀尖越来越大、压的自己几乎透不过气，"
                               HIR "直至猛然一呕血，却发现" + weapon->name() + "已经在自己身上留下狰狞的轨迹。\n" NOR;
                        target->die(me);
                }
        } else
        {
                me->start_busy(2);
                msg += CYN "正当这刀要落在$n" CYN "身上，$N" CYN "浑身一颤，血光骤减，$n" CYN "顺势滚到一旁，已是不成招法，躲过了$N"
                       CYN "的必杀一刀。\n"NOR;
                addn("neili", -100, me);
        }
        
        message_combatd(msg, me, target);
        return 1;
}
