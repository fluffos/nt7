// This is player's own skill (Write by Lonely@nt2)
// Create by 渡欧(Ssyunone) at Sun Mar  8 19:13:00 2015
// 无色无相神剑(wusewx-sword.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "HIW$NHIW一招击在$nHIW身上，却被$nHIW暗运易筋经内功，将内力尽数移入地下。\nNOR,HIW$n轻轻一带，$NHIW发现自己招数回击过来，吓得往后倒退几步。\nNOR,HIW$n手臂回转，在$NHIW手肘下轻轻一推，$NHIW招数落空。\nNOR,HIW$n右手伸出，在$NHIW手腕上轻轻一拉，$NHIW收势不住，直往前扑去。\nNOR,HIW$n身形不动，$NHIW一招击下，有如石沉大海，不觉呆住了。\nNOR,HIW$n左牵右引，$NHIW如身处漩流，连续转了好几个圈。\nNOR,HIW$n双手回圈，$NHIW只觉得前面好象有一堵墙，再也攻不进去。\nNOR,HIW$n轻轻一转，$NHIW一招击在地上，只打得尘土飞扬。\nNOR。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "刺伤",
	"skill_name" : "降妖伏魔"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
        object weapon; 
        
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
                
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练" + "无色无相神剑" + "。\n");
                
        return 1;
}

int valid_enable(string usage) { 
        return usage == "sword" || 
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
        level = (int)me->query_skill("wusewx-sword",1);
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

        lvl = me->query_skill("wusewx-sword", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int practice_skill(object me)
{
        object weapon; 
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");        
        
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
        return __DIR__ + "wusewx-sword" + "/" + action; 
}
string query_description()
{
	return
 "无色无相神剑是创自渡欧的绝世剑法，招式勇往直前，大开大阖，以勇猛
霸道而著称，当初江湖十大掌门围攻渡欧的时候，情势万分危机，渡欧在
千钧一发之际使出这套武功，顿时风云变色，化险为夷…该剑法大舟小舟
无不载，大鱼小鱼无不容，是剑法和禅宗心法的极致结晶… '.'" ; 
}
