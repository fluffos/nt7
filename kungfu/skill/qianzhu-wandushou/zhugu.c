#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "蛛蛊决"; }

#include "/kungfu/skill/eff_msg.h";
string final(object me, object target, int lvl);
int perform(object me, object target)
{
        string msg;
        int lvl;
        int damage;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("这里不能攻击别人！\n");

        if (! target || ! target->is_character())
                return notify_fail("你要对谁施展蛛蛊决？\n");

        if( query("not_living", target) )
                return notify_fail("看清楚，那不是活人。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功火候不足以施展蛛蛊决。\n");

        if ((int)me->query_skill("qianzhu-wandushou", 1) < 130)
                return notify_fail("你的千蛛万毒手修为不够，现在还无法施展蛛蛊决。\n");

        if (me->query_skill_mapped("hand") != "qianzhu-wandushou")
                return notify_fail("你没有激发千蛛万毒手，无法施展蛛蛊决。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真气不够，现在无法施展蛛蛊决。\n");

        msg = HIB "$N" HIB "施出蛛蛊决，只见一缕黑气从"
              "指尖透出，只一闪就没入了$n" HIB "的眉心！\n" NOR;

        ap = attack_power(me,"hand");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");
                damage+= query("jiali", me);
                damage*=3;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
					   (: final, me, target, lvl :));
                addn("neili", -320, me);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "运足内力，以深厚的内功"
                       "化解了这一指的毒劲。\n" NOR;
                me->start_busy(3);
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);
        /*
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);
        */
        return 1;
}

string final(object me, object target, int lvl) 
{ 
          target->affect_by("qianzhu_wandushou",
                            ([ "level" : lvl + random(lvl / 2),
                               "id":query("id", me), 
                               "duration" : lvl / 40 + random(lvl / 15) ]));
  
          return HIR "$n" HIR "只觉得一股如山的劲力顺指尖猛"
                 "攻过来，只觉得全身毒气狂窜，“哇”的一声"
                 "吐出一口黑血！\n" NOR;
} 
