// freezing-force.c 少林 冰蚕寒功
// Feb.21 1998 by Java

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

int valid_force(string force)
{
        return 1;
        return force == "guixi-gong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("freezing-force", 1);
        return lvl * lvl * 22 * 18 / 100 / 200;
}

int valid_learn(object me)
{
        if( (!me->query_family() || 
            me->query_family() != "星宿派") && !query("yuanshen", me) ) 
                return notify_fail("你不是星宿派门人，无法学习此神功。\n");

        if (me->query_skill("force", 1) < 50)
                return notify_fail("你的基本内功火候不够，难以锻炼冰蚕寒功！\n");

/*
        if (me->query_skill("yijinjing", 1))
                me->delete_skill("yijinjing");
*/

        if (me->query_skill("force", 1) < me->query_skill("freezing-force", 1))
                return notify_fail("你的基本内功水平不够，难以锻炼更深厚的冰蚕寒功！\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("冰蚕寒功无法通过简单的练习来增加熟练度。\n");
}

// hit effect called by combatd
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        mixed result;
        int lvl;
        int flvl;

        result = ::hit_ob(me, victim, damage_bonus, factor);
        if (intp(result) && result > 0)
        {
                lvl  = me->query_skill("freezing-force", 1);
                flvl=query("jiali", me);
                if (lvl < 80 || flvl < 10)
                        return;

                if (flvl * 2 + random(lvl) > victim->query_skill("force"))
                {
                        victim->affect_by("freezing",
                                ([ "level" : flvl * 3 / 2 + random(flvl / 2),
                                   "id":query("id", me),
                                   "duration" : lvl / 40 + random(lvl / 20) ]));

                        return ([ "damage" : result * 2,
                                  "msg" : HIW "霎时$n" HIW "只觉得寒风袭"
                                          "体，有种说不出的难受。\n" NOR ]);
                }
        }

        return result;
}

string exert_function_file(string func)
{
        return __DIR__"freezing-force/" + func;
}

string *fanzhen_msg = ({
        "只震得$N胸内腹中，有如五脏一齐翻转！\n",
        "抢先反震，将$N震得脸如白纸，全无血色！\n",
        "震得$N心肺欲裂，腾腾腾连退数步！\n",
        "功力已布满全身，将$N的力量反震回去！\n",
        "震得$N天旋地转，腾腾腾连退七八步！\n",
        "和$N一撞，只震的$p胸口气血翻涌！\n",
        "$N便如撞在一堵棉花作面，钢铁为里的厚墙上一般，震退数步！\n",
        "$N刚碰到$p，突然身子一震，登时飞了出去！\n",
});
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        string msg;
        int ap, dp;
        int jiali;
        object weapon1;
        
        if ((int) me->query_skill("freezing-force", 1) < 200 ||
            ! living(me))
                return;                      

        if( (jiali=query("jiali", ob))<1 )
                return;

        ap=ob->query_skill("force")+query("neili", ob)+
             ob->query_skill("count", 1);
        dp=me->query_skill("force")+query("neili", me);

        if (ap / 2 + random(ap) < dp)
        {
                if( !objectp(weapon1=query_temp("weapon", ob)) )
                {
                        result = ([ "damage" : -damage ]);
                        
                        msg = random(2) ? HIR "$n身上生出一股反震之力，" : HIR "$n身上冰蚕寒功随心而起，";   
                              
                        msg += fanzhen_msg[random(sizeof(fanzhen_msg))] + NOR;             
                
                        ob->receive_damage("qi", damage, me);
                        ob->receive_wound("qi", damage / 2, me);      
                        
                        result += ([ "msg" : msg ]);
                        
                        return result;
                } else
                {
                        result = ([ "damage" : -damage ]);

                        switch (random(5))
                        {
                        case 0:  
                        case 1:
                        case 2:
                        case 3:                                                
                                result += ([ "msg" : HIR "好似有一堵无形的墙在$n面前阻挡着，结果"
                                                     "$N" HIR "一下子被反弹，震得$N" 
                                                     HIR "手臂发麻！\n" NOR ]);
                                break;
                        default:
                                result += ([ "msg" : HIR "结果$n身上生出一股反震之力，$N只觉虎口一热，" + 
                                                     weapon1->name() + HIR "顿时脱手而出，飞出丈外！\n" NOR]);
                                weapon1->unequip();
                                weapon1->move(environment(ob));
                                ob->reset_action();
                                if (! ob->is_busy())
                                        ob->start_busy(1);
                                break;
                        }

                        return result;
                }
        }
}
