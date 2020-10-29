// This program is a part of NITAN MudLIB 
// redl 2015.2
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return YEL "百毒金蚕蛊" NOR; }

int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill;
        int i;
        int addhp;
        int maxnum, cnum, cdtime, time;
        mapping buff;
        object *bugs;
        int canlv = query("can_perform/qianzhu-wandushou/jin", me);
        
        if (me->query_skill_prepared("hand") != "qianzhu-wandushou")
                return notify_fail("你没有准备使用千蛛万毒手，无法召唤百毒金蚕蛊。\n");

        skill = me->query_skill("qianzhu-wandushou", 1);

        if (skill < 650)
                return notify_fail("你的千蛛万毒手修为有限，无法召唤百毒金蚕蛊。\n");

        if (me->query_skill("force") < 380)
                return notify_fail("你的内功火候不够，难以召唤百毒金蚕蛊。\n");

        if( query("max_neili", me)<20000 )
                return notify_fail("你的内力修为没有达到那个境界，无法运转内力召唤百毒金蚕蛊。\n");

        if( query("neili", me)<3000 )
                return notify_fail("你的真气不够，现在无法召唤百毒金蚕蛊。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必须是空手才能召唤百毒金蚕蛊。\n");

                if( (cdtime = BUFF_D->get_buff_overtime(me, "wdaq_bdjcg")) > 0 )
                return notify_fail(MAG"百毒金蚕蛊消耗心神太甚，还需等待"+cdtime+"秒。\n"NOR);
                
        maxnum = 1 + ABILITY_D->check_ability(me, "max-bdjcg-summon") / 10;
        bugs = query_temp("bugs/bdjcg", me);
        if (!bugs || undefinedp(bugs) || !arrayp(bugs) || !sizeof(bugs))
                bugs = ({});
        else
                bugs = filter_array(bugs, (: $1 && objectp($1) :));
        cnum = sizeof(bugs);
        if( cnum >= maxnum )
                return notify_fail("你召唤百毒金蚕蛊群数量已经达到上限。\n");

                target = new("/d/wudu/npc/jincangu");
                bugs += ({target});
                set_temp("bugs/bdjcg", bugs, me);

        msg = NOR HIC "\n$N" NOR HIC "伸出手指往自己的眉心一点，只见印堂间现出一个小孔，\n其间有金色的小虫"
              "源源不断地飞出来，正是百蛮山豢养的" HIB "百毒" NOR YEL "金蚕蛊" NOR HIC 
              "。\n中途$n" NOR HIC "转头对冲主人就是一啃，$N" NOR HIC "全身精血一衰。\n" NOR;
                
                message_vision(msg, me, target);
                set("jing", query("jing", me)/2, me);
                set("eff_jing", query("eff_jing", me)/2, me);
                set("qi", query("qi", me)/2, me);
                set("eff_qi", query("eff_qi", me)/2, me);
                COMBAT_D->report_status(me);
                message_vision("\n", me, target);
                addhp = (query("eff_qi", me) + query("eff_jing", me)) / 1000000;
                addhp = addhp * (100 + 4* ABILITY_D->check_ability(me, "hp-bdjcg"));
                set("owneradd", addhp, target);
                set_temp("owner", me, target);
                set_temp("owner_name", query("name", me), target);
                set_temp("owner_id", query("id", me), target);
                set("owner", me, target);
                set("owner_name", query("name", me), target);
                set("owner_id", query("id", me), target);
                set("ridable", 0, target);
                set("ab/reduce_damage-bdjcg", ABILITY_D->check_ability(me, "reduce_damage-bdjcg") / 5, target);
                set("ab/avoid_die-bdjcg", ABILITY_D->check_ability(me, "avoid_die-bdjcg") / 5, target);
                
                if (query("levelp", target)<canlv) {
                        set("levelp", canlv-1, target);
                target->levelup();
        }
        target->move(environment(me));
        target->heart_beat_p();
        //target->command("follow "+query("id", me));
        //target->command("guard "+query("id", me));
                        
        addn("neili", -1500, me);
        target->start_busy(2 + random(2));
        me->start_busy(2 + random(3));

                if (!playerp(me)) {
                        me->full_self();
                        return 1;
                }
                                
                                target->receive_damage("jing", 2500000);
                                target->receive_wound("jing", 2500000);
                                target->receive_damage("qi", 5000000);
                                target->receive_wound("qi", 5000000);
                
                time = 60 * (30 - ABILITY_D->check_ability(me, "cd-bdjcg-summon"));
                buff = ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "wdaq_bdjcg",
                "attr"   : "curse",
                "name"   : "千蛛万毒手·百毒金蚕蛊",
                "time"   : time,
                "buff_msg" : "百毒金蚕蛊消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
                ]);
                BUFF_D->buffup(buff);
                
        return 1;
}

