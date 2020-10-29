#include <ansi.h>
#include <combat.h>

string name() { return HIR "阴阳磨" NOR; }

inherit F_SSERVER;

string finala(object me, object target, int damage);
string finalb(object me, object target, int damage);

int perform(object me, object target)
{
        string msg;
        int ap, dp, dd;
        int damage;
        int fmsk = me->query_skill("tiezhang-shuishangpiao", 1);
        int delta;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("tie-zhang", 1) < 220)
                return notify_fail("你铁掌掌法火候不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("你没有激发铁掌掌法，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("你没有准备铁掌掌法，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "施出铁掌绝技「" HIR "阴阳磨"
              HIW "」，左掌不着半点力道，携着阴寒劲向$n"
              HIW "拂去。\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*15;
        dp=defense_power(target,"parry")+target->query_con()*15;
        dd=defense_power(target,"dodge")+target->query_dex()*15;
        
        damage = damage_power(me,"strike");
        damage+= fmsk;
        
        delta = ABILITY_D->check_ability(me, "ap_power-tie-yin"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        delta = ABILITY_D->check_ability(me, "da_power-tie-yin"); // 门派ab
        if( delta ) damage += damage*delta/100;
                
        if (ap / 2 + random(ap) + fmsk / 2 > dp)
        {
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 75+fmsk/10,
                                           (: finala, me, target :));
        } else
        {
                msg += CYN "$n" CYN "见$N" CYN "掌出如风，心知"
                       "此招后着极是凌厉，当即斜跳闪开。\n" NOR;
        }

        msg += HIR "\n紧接着$N" HIR "右掌一振，掌风过处，竟席"
               "卷起一股热浪，向$n" HIR "胸前猛然拍落。\n" NOR;

        if (ap / 2 + random(ap) + fmsk / 2 > dd)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80+fmsk/10,
                                           (: finalb, me, target :));
        } else
        {
                msg += CYN "$n" CYN "忽闻呼啸声大至，眼见$N" CYN
                       "掌势如虹，急忙纵跃躲避开来。\n" NOR;
        }
        me->start_busy(3 + random(2));
        addn("neili", -400, me);
        message_combatd(msg, me, target);
        return 1;
}

string finala(object me, object target, int damage)
{
        int lvl;
        lvl = me->query_skill("strike");

        target->affect_by("tiezhang_yin",
                       (["level":query("jiali", me)+random(query("jiali", me)/2),
                          "id":query("id", me),
                          "duration" : lvl / 50 + random(lvl / 50) ]));

        return HIW "霎那间$n" HIW "已被$N" HIW "阴寒掌劲拂中要"
               "害，不由得浑身一颤，难受之极。\n" NOR;
}

string finalb(object me, object target, int damage)
{
        int lvl;
        lvl = me->query_skill("strike");

        target->affect_by("tiezhang_yang",
                       (["level":query("jiali", me)+random(query("jiali", me)/2),
                          "id":query("id", me),
                          "duration" : lvl / 50 + random(lvl / 50) ]));

        return HIR "只听嗤的一声，$N" HIR "右掌如击败革，正中"
               "$n" HIR "胸口，震断了数根肋骨。\n" NOR;
}