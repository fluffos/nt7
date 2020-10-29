// jue.c 绝仙决
 
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
                return notify_fail("绝仙决只能对战斗中的对手使用。\n");
 
        if (me->query_skill("bluesea-force", 1) < 120)
                return notify_fail("你的南海玄功还不够娴熟，不能使用绝仙决！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的内力不够，不能使用绝仙决！\n");
 
       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "哈哈大笑，一掌挥出，变化出满天掌影，封住了$n"
              HIC "所有的退路！\n" NOR;
 
        ap=attack_power(me,"force")+query("con", me)*20;
        dp=defense_power(target,"parry")+query("dex", target)*20;

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
                                           HIR "$n" HIR "竭力腾挪躲闪，却听“啪”的"
                                           "一声被$P" HIR "结结实实的打在了胸前，登"
                                           "时吐血不止！\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}