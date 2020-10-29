// by rcwiz for yhonline
// 入梦神功

#include <ansi.h>

inherit FORCE;

string *dodge_msg = ({
        HIW "$n" HIW "手足忽的一晃，$N" HIW "竟然无法进击，只能自保。\n" NOR,
        HIW "只见$n" HIW "身子轻轻晃动，$N" HIW "眼前顿时出现了无数个$n" HIW
        "的幻影，令$N" HIW "完全无法辨出虚实。\n" NOR,
        HIW "$n" HIW "往旁边歪歪斜斜的迈出一步，却恰好令$N" HIW "的攻击失之"
        "毫厘。\n" NOR,
        HIW "$N" HIW "这一招来的好快，然后$n" HIW "一闪，似乎不费半点力气，"
        "却将$N" HIW "这一招刚好避开。\n" NOR,
        HIW "但见$n" HIW "轻轻一跃，已不见了踪影，$N" HIW "心中大骇，却又见"
        "$n" HIW "擦肩奔过，步法之奇巧，当真令人思索菲仪。\n" NOR,
});

string *parry_msg = ({
        HIW "$N" HIW "一招击在$n" HIW "身上，力道竟消失得无影无踪！\n" NOR,
        HIW "$n轻轻一带，$N" HIW "发现自己招数回击过来，吓得往后倒退几步。\n" NOR,
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bagua-shengong", 1);
        return lvl * lvl * 15 * 40 / 100 / 200;
}

mapping *action = ({
([
        "action": HIW "$N" HIW "单手一挥，刹那间狂风骤起， 令人不寒而栗。" NOR,
        "attack": 999,
        "dodge" : 999,
        "parry" : 999,
        "damage": 999,
        "force" : 999,
        "damage_type":  "神伤"
]),
([
        "action": HIG "$N" HIG "神情微变，猛然间狂风暴雨，天色大变。" NOR,
        "attack": 999,
        "dodge" : 999,
        "parry" : 999,
        "damage": 999,
        "force" : 999,
        "damage_type":  "神伤"
]),
});

string *usage_skills = ({ "unarmed", "strike", "claw", "hand", "cuff", "finger",
                          "sword", "blade", "hammer", "throwing", "club", "whip",
                          "staff", "dodge", "dagger", "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force)
{
        return 1;
}

int double_attack()
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object ob;
        int lvl;
        
        lvl = me->query_skill("force");
        
        if( query_temp("baguazhen", victim) >= 3 )
        {
                if (lvl / 2 + random(lvl) > victim->query_skill("force") )
                {
                      if (random(2))
                      {
                           victim->receive_wound("qi", 300);
                           addn("jing", -50, victim);
                      }
                      else 
                      {
                           message_vision(HIR "$N" HIR "对着$n" HIR "需点几下，$n" HIR 
                                          "竟无法动弹了。\n" NOR, me, victim);
                                     
                           victim->start_busy(20 + random(20));                                            
                      }
                }
                return;
        }

        if (random(20) == 1)
        {
                message_vision(NOR + HIG "猛然间一阵青烟飘过，诸葛亮已"
                               "经不见了影踪 ……\n", me, victim);               

                victim->move("/kungfu/class/sky/bagua");

                return;                
        }

        victim->receive_wound("qi", 500);
        addn("jing", -30, victim);

        return;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;

        if (random(10) == 0)
        {
                result = ([ "damage": -damage ]);

                result += (["msg" : HIW "$n" HIW "凌空虚点几下，猛然间不见了踪影。\n" NOR]);

                return result;
        }
}


