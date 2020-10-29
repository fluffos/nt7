// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

string name() { return HIW "极境" NOR; }

int perform(object me, object target)
{
        mapping buff;
        object *obs;
        string msg;
        int damage;
        int ap, dp;
        int flag;
        int i;
        int p;
        int delta;
        int time;
        int fmsk = me->query_skill("guangming-jing", 1);

        if( query("yuanshen_level", me) < 1 )
                return notify_fail(name() + "需要修炼成元神后才能使用。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail(name() + "只能空手施展。\n");

        if (query("max_neili", me) < 8000)
                return notify_fail("你的内力的修为不够，现在无法使用" + name() + "。\n");

        if (me->query_skill("jiuyang-shengong", 1) < 250)
                return notify_fail("你的九阳神功还不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "jiuyang-shengong")
                return notify_fail("你现在没有激发九阳神功为拳脚，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("你现在没有激发九阳神功为内功，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "jiuyang-shengong")
                return notify_fail("你现在没有准备使用九阳神功，难以施展" + name() + "。\n");

        if ((int)query("neili", me) < 2000)
                return notify_fail("你的真气不够，无法运用" + name() + "。\n");
        
        if( userp(me) ) 
        {
                  if( (time = BUFF_D->get_buff_overtime(me, "jysg_ji")) > 0 )
                        return notify_fail(MAG"魔光日无极(极境)消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        msg = HIY "只见$N" HIY "双目微闭，单手托天。掌心顿时腾起一个无比刺眼的"
              "气团，正是奥\n义「" NOR + HIW "魔光日无极" NOR + HIY "」。霎时"
              "金光万道，尘沙四起，空气炽热，几欲沸腾。$N" HIY "\n随即收拢掌心"
              "，气团爆裂开来，向四周电射而出，光芒足以和日月争辉。\n\n" NOR;

        addn("neili", -1000, me);

        ap = attack_power(me, "unarmed");
        ap *= 2;
        
        delta = ABILITY_D->check_ability(me, "ap_power-jysg-ri"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        damage = attack_power(me, "force");
        damage+= query("jiali", me);
        damage+= me->query_all_buff("unarmed_damage");
        damage+= damage / 300 * me->query_str();
        damage+= damage*(fmsk/100)*5/100;
                        
        delta = ABILITY_D->check_ability(me, "da_power-jysg-ri"); // 门派ab
        if( delta ) damage += damage*delta/100;
        
                if( target->query_family() == "星宿派" || target->query_family() == "逍遥派" )
                        damage *= 3;
                        
                dp = defense_power(target, "force");
                if (ap + random(ap) + fmsk > dp)
                {
                        msg += HIR "$n只觉眼前金光万道，周围空气几欲沸腾，光芒便如千万细针一齐扎入身体般。\n" NOR;
                        msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 300+fmsk/15,
                                        HIR "光芒闪过，$n" HIR "却是呆立当场，动也不动，七"
                                        "窍流血，神情扭曲，煞是恐怖。\n" NOR);
                } 
                else
                {
                        msg += HIY "$N只觉眼前金光万道，周围空气几欲沸腾，大惊之下连忙急运内功，抵御开来。\n" NOR;
                }
                message_combatd(msg, me, target);
                time  = 40;
                time -= ABILITY_D->check_ability(me, "cd-jysg-ri"); // ab门派减cd
                time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
                
                buff = ([
                        "caster" : me,
                        "target" : me,
                        "type"   : "cooldown",
                             "type2"  : "jysg_ji",
                        "attr"   : "curse",
                          "name"   : "九阳神功·极境",
                        "time"   : time,
                         "buff_msg" : "极境消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                        "disa_msg" : "",
                        "disa_type": 0,
                ]);
        
                BUFF_D->buffup(buff);
                me->start_busy(5);
                return 1;
        
}
