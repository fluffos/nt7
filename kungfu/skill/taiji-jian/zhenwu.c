// zhenwu.c 真武除邪

#include <ansi.h>
#include <combat.h>

string name() { return "真武除邪"; }

inherit F_SSERVER;

string final(object me, object target, int damage);
int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;
        int fmsk;
        int delta;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「" + name() + "」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query_skill("taiji-jian", 1) < 250)
                return notify_fail("你的太极剑法不够娴熟，不会使用「" + name() + "」。\n");

        if ((int)me->query_skill("force", 1) < 250)
                return notify_fail("你的内功修为不够高，难以运用「" + name() + "」。\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 250)
                return notify_fail("你的太极神功修为不够高，难以运用「" + name() + "」。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你现在真气不够，不能使用「" + name() + "」。\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("你没有激发太极剑法，不能使用「" + name() + "」。\n");

        msg = HIY "$N" HIY "闭目凝神，心如点转，一招充满太极剑意的「" HIW + name() +
              HIY "」缓缓使出，剑招返朴归真，看似平淡无奇，\n实则汇集了天地之间的正气，"
              HIY "由手中" + weapon->name()+ "幻化出无数太极剑圈，铺天盖地的压向$n！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");


        if( query("id", weapon) == "zhenwu jian") ap+=ap*(20+random(10))/100;
        if (target->is_bad()) ap += ap / 2;

        /*
        if (me->is_not_good()) ap = ap / 2;
        if (me->is_bad()) ap = ap / 3;
        if (target->is_good()) ap = ap * 4 / 5;
        */
        
        delta = ABILITY_D->check_ability(me, "ap_power-tjj-zhenwu"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        fmsk = me->query_skill("tianwei-zhengqi", 1);
        if( wizardp(me) && query("env/combat_test", me) )
        {
                tell_object(me, HIY "AP: " + ap + ". DP: " + dp + ".\n" NOR);
        }
        if (ap / 2 + random(ap*4/3) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
        
                delta = ABILITY_D->check_ability(me, "da_power-tjj-zhenwu"); // 门派ab
                if( delta ) damage += damage*delta/100;
        
                addn("neili", -500, me);
                //tell_object(me, HIC "DAMAGE: " + damage + ".\n" NOR);
                //msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 285,
                //                           HIR "\n$p" HIR "被$P的正气所慑，竟然吓得顾不上招架，"
                //                           "这一剑自胸口向小腹横划而过，\n顿时鲜血飞溅！\n" NOR);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 285+fmsk/5,
                                           (: final, me, target, damage :));
                me->start_busy(2);
        } else
        {
                msg += HIG "可是$p" HIG "看破了$P" HIG "的企图，镇"
                       "定逾恒，全神应对自如。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 3, me);
        target->receive_wound("jing", damage / 6, me);
        return  HIY "结果$p" HIY "没有把它放在心上，随"
                "手应了一招，却见$P" HIY "剑势忽然一变"
                "，\n气象万千，变幻无穷，极具王者风范！\n"
                HIR "$p" HIR "惊慌失措，呆在当场，被$P"
                HIR "这一剑击中要害！鲜血崩流，惨不忍睹！\n" NOR;
}
