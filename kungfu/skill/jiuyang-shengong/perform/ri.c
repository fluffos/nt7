// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

string name() { return HIW "魔光日无极" NOR; }

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

        me->clean_up_enemy();
        if (! me->is_fighting())
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
                if( (time = BUFF_D->get_buff_overtime(me, "jysg_ri")) > 0 )
                        return notify_fail(MAG"魔光日无极消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        msg = HIY "只见$N" HIY "双目微闭，单手托天。掌心顿时腾起一个无比刺眼的"
              "气团，正是奥\n义「" NOR + HIW "魔光日无极" NOR + HIY "」。霎时"
              "金光万道，尘沙四起，空气炽热，几欲沸腾。$N" HIY "\n随即收拢掌心"
              "，气团爆裂开来，向四周电射而出，光芒足以和日月争辉。\n\n" NOR;

        message_combatd(msg, me);

        addn("neili", -1000, me);

        ap = attack_power(me, "unarmed") + me->query_con()*10;
        
        delta = ABILITY_D->check_ability(me, "ap_power-jysg-ri"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        damage = attack_power(me, "force");
        damage+= query("jiali", me);
        damage+= damage*(fmsk/100)*5/100;
        damage *= 3;
        damage+= random(damage);
                        
        delta = ABILITY_D->check_ability(me, "da_power-jysg-ri"); // 门派ab
        if( delta ) damage += damage*delta/100;
        
        obs = me->query_enemy();
        for (flag = 0, i = 0; i < sizeof(obs); i++)
        {
                dp = defense_power(obs[i], "force") + obs[i]->query_con()*10;

                if (ap / 2 + random(ap) + fmsk > dp)
                {
                        switch (random(2))
                        {
                        case 0:
                                tell_object(obs[i], HIR "你只觉眼前金光万道，周围空气几欲沸"
                                                    "腾，光芒便如利箭一般透体而入。\n" NOR);
                                break;

                        default:
                                tell_object(obs[i], HIR "你只觉眼前金光万道，周围空气几欲沸"
                                                    "腾，光芒便如千万细针一齐扎入身体般。\n"
                                                    NOR);
                                break;
                        }
                        if( obs[i]->query_family() == "星宿派" || obs[i]->query_family() == "逍遥派" )
                        {         
                                obs[i]->receive_damage("qi", damage*3, me);
                                obs[i]->receive_wound("qi", damage*3, me);

                                obs[i]->receive_damage("jing", damage * 18, me);
                                obs[i]->receive_wound("jing", damage * 9, me);
                        }
                        else
                        {            
                                obs[i]->receive_damage("qi", damage, me);
                                obs[i]->receive_wound("qi", damage, me);

                                obs[i]->receive_damage("jing", damage * 6, me);
                                obs[i]->receive_wound("jing", damage * 3, me);
                        }

                        p = (int)query("qi", obs[i]) * 100 / (int)query("max_qi", obs[i]);

                        switch (random(5))
                        {
                        case 0:
                                msg = HIR "只听" + obs[i]->name() +
                                      HIR "一声惨嚎，接连退了数步，“"
                                      "哇”的呕出一大口鲜血。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 1:
                                msg = HIR "只见" + obs[i]->name() +
                                      HIR "向后飞出丈远，重重的跌落在"
                                      "地上，衣衫烧焦，再也没力气站起"
                                      "。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 2:
                                msg = HIR "只见" + obs[i]->name() +
                                      HIR "跌跌撞撞向后连退数步，伏倒"
                                      "在地。须眉、衣衫都发出一股焦臭"
                                      "。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 3:
                                msg = HIR "光芒闪过，" + obs[i]->name() +
                                      HIR "却是呆立当场，动也不动，七"
                                      "窍流血，神情扭曲，煞是恐怖。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        default:
                                msg = HIR + obs[i]->name() +
                                      HIR "急忙抽身后退，可只见眼前光"
                                      "芒暴涨，一闪而过。全身已多了数"
                                      "个伤口，鲜血飞溅。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;
                        }
                        if (! obs[i]->is_busy())
                                obs[i]->start_busy(1);
                        message("vision", msg, environment(me), ({ obs[i] }));
                        addn("neili", -500, obs[i]);
                        flag = 1;
                } else
                {
                        tell_object(obs[i], HIY "你只觉眼前金光万道，周围空气几"
                                            "欲沸腾，大惊之下连忙急运内功，抵御"
                                            "开来。\n" NOR);
                }
                if (query("neili", obs[i]) < 0)
                        set("neili", 0, obs[i]);
        }

        if (! flag)
                message_combatd(HIY "只见光芒顿敛，却没有任何人被$N"
                               HIY "这招击中。\n\n" NOR, me, 0, obs);
        
        time  = 40;
        time -= ABILITY_D->check_ability(me, "cd-jysg-ri"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
                
        buff = ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "jysg_ri",
                "attr"   : "curse",
                "name"   : "九阳神功·魔光日无极",
                "time"   : time,
                "buff_msg" : "魔光日无极消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);
        
        BUFF_D->buffup(buff);
        me->start_busy(5);
        return 1;
}
