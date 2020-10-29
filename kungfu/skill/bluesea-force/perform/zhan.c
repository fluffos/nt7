// zhan.c 斩仙决
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("斩仙决只能对战斗中的对手使用。\n");
 
        if (me->query_skill("bluesea-force", 1) < 120)
                return notify_fail("你的南海玄功还不够娴熟，不能使用斩仙决！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的内力不够，不能使用斩仙决！\n");
 
       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "面容肃穆，倏的一掌拍出，虚虚实"
              "实的攻向$n" HIC "，变化令人难以捉摸。\n" NOR;
 
        ap = attack_power(me, "force") + me->query_con();
        dp = defense_power(target, "parry") + target->query_str();

        me->start_busy(2);
        addn("neili", -50, me);
        if (ap / 2 + random(ap) < dp)
        {
                msg += HIG "然而$n" HIG "看破了$N" HIG
                       "的掌势，不慌不忙的躲过了这一击！\n" NOR;
        } else
        {
                addn("neili", -75, me);
                damage = damage_power(me, "force");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                           HIR "$n" HIR "稍一犹豫，被这一掌击了"
                                           "个正中！接连退了几步，吐了一地的血。\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}