#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";
string final(object me, object target, int lvl);
string name() { return "万毒穿心"; }

int perform(object me, object target)
{
        string msg;
        int lvl;
        int ap, dp;
        int damage;
        int delta;
        int fmsk = me->query_skill("wudu-jing", 1);

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你还没有悟道，暂时不能施展"+name()+"。\n");

        if( me->is_busy() )
                return notify_fail("你正忙着呢。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("「万毒穿心」只能空手才能施展。\n");

        if (! me->is_fighting(target))
                return notify_fail("「万毒穿心」只能对战斗中的对手使用。\n");

        if (! target || ! target->is_character())
                return notify_fail("你要对谁施展万毒穿心？\n");

        if (! living(target))
                return notify_fail("看清楚，那不是活人。\n");

        if ((int)me->query_skill("wudu-qishu", 1 ) < 300)
                return notify_fail("你的五毒奇术火候不足以施展万毒穿心。\n");

        if ((int)me->query_skill("wudu-jing", 1 ) < 300)
                return notify_fail("你的五毒阱火候不足以施展万毒穿心。\n");

        if ((int)me->query_skill("qianzhu-wandushou", 1) < 800)
                return notify_fail("你的千蛛万毒手修为不够，现在还无法施展万毒穿心。\n");

        if (me->query_skill_prepared("hand") != "qianzhu-wandushou")
                return notify_fail("你没有准备千蛛万毒手，无法施展万毒穿心。\n");

        if( query("neili", me)<4000 )
                return notify_fail("你的真气不够，现在无法施展万毒穿心。\n");

        msg = HIY "$N" HIY "双手猛然翻转向前，掌间隐现阵阵黑气，凶险无比，掌风到处，数股"
              "黑气喷射而出，直奔$n" HIY "胸口。\n" NOR;

        ap = attack_power(me, "hand") + fmsk;
        dp = defense_power(target, "force");
        
        delta = ABILITY_D->check_ability(me, "ap_power-qzwds-chuan"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");
                damage+= query("jiali", me);
                damage *= 12 + (query("level", me) / 3);
                
                delta = ABILITY_D->check_ability(me, "da_power-qzwds-chuan"); // 门派ab
                if( delta ) damage += damage*delta/100;
        
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 400,
                                           (: final, me, target, lvl :));

                addn("neili", -4000, me);
                me->start_busy(2 + random(2));
        } else
        {
                msg += CYN "可是$p" CYN "运足内力，以深厚的内功"
                       "化解了这一指的毒劲。\n" NOR;
                me->start_busy(4);
                addn("neili", -3000, me);
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
        if (! userp(target))
                target->affect_by("wandu_chuanxin",
                                    ([ "level" : lvl * 100,
                                       "id":query("id", me),
                                       "duration" : lvl / 10 + random(lvl / 10) ]));
        else
                target->affect_by("wandu_chuanxin",
                                    ([ "level" : lvl * 50,
                                       "id":query("id", me),
                                       "duration" : lvl / 10 + random(lvl / 10) ]));

        return HIR "$n" HIR "只觉得数股毒气透心而过，说不出的难受。\n" NOR;
}
