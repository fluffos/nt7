// This is player's own skill (Write by Lonely@nt2)
// Create by 剑人(Dlf) at Sat Mar  7 20:08:55 2015
// 龙凤爪(longfeng-claw.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N两臂紧伸，腿脚尖点地，一式「临」，死死的包住$n往半空中自旋而上",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "瘀伤",
	"skill_name" : "临"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练"+"龙凤爪"+"。\n");
        return 1;
}

int valid_enable(string usage) { 
        return usage == "claw" || 
               usage == "parry"; 
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("longfeng-claw",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

mixed *query_actions() { return action; }

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("longfeng-claw", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
 
int practice_skill(object me)
{
        if( query("qi", me)<25 )
                return notify_fail("你的体力不够了，休息一下再练吧。\n");
        if( query("neili", me)<3 )
                return notify_fail("你的内力不够了，休息一下再练吧。\n");
        me->receive_damage("qi", 25);
        addn("neili", -3, me);
        return 1;
} 

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        if (damage < 100) return 0;

        if (random(damage) > victim->query_str()) 
        {
                result = ([ "damage" : damage ]);
                result += ([ "msg" : HIW "你听到「喀嚓」一声轻响，已被$N的兵器所发杀气挫伤，$n顿时血冒三丈！！！\n" NOR ]);

                return result;
        }
}

string perform_action_file(string action) 
{
        return __DIR__ + "longfeng-claw" + "/" + action; 
}
string query_description()
{
	return
 "龙凤爪是创自龙凤的绝世爪法，招式勇往直前，大开大阖，以勇猛霸道而
著称，当初江湖十大掌门围攻剑人的时候，情势万分危机，龙凤在千钧一
发之际使出这套武功，顿时风云变色，化险为夷……" ; 
}
