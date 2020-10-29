// This is player's own skill (Write by Lonely@nt2)
//Createby小妖(Sata)atTue May 10 13:11:08 2011
// 灵犀一指指(lingxi-zhi-finger.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N双臂微曲，两拳紧握，一式「灵光乍现」，双手食指猛的点向$n。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "瘀伤",
	"skill_name" : "灵光乍现"
 ]),
// ZHAOSHI : 1
([      "action" : "$N两臂紧伸，腿脚尖点地，一式「一指惊天」，双手剑指紧握对准$n的$l用尽全身力气戳了上去。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 110,
	"damage_type" : "瘀伤",
	"skill_name" : "一指惊天"
 ]),
// ZHAOSHI : 2
([      "action" : "$N两臂紧伸，腿脚尖点地，一式「一指定坤」，左手中指直接指向$n的$l",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 120,
	"damage_type" : "瘀伤",
	"skill_name" : "一指定坤"
 ]),
// ZHAOSHI : 3
([      "action" : "$N两臂紧伸，一式「定江山」，右手大拇指直指$n的$l而去",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 130,
	"damage_type" : "瘀伤",
	"skill_name" : "定江山"
 ]),
// ZHAOSHI : 4
([      "action" : "$N双掌十指并齐，一式「千军破」，带着罡风死死的锁住$n。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 140,
	"damage_type" : "瘀伤",
	"skill_name" : "千军破"
 ]),
// ZHAOSHI : 5
});

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练"+"灵犀一指指"+"必须空手。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练"+"灵犀一指指"+"。\n");
        return 1;
}

int valid_enable(string usage) { 
        return usage == "finger" || 
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
        level = (int)me->query_skill("lingxi-zhi-finger",1);
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

        lvl = me->query_skill("lingxi-zhi-finger", 1);
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
                result += ([ "msg" : HIW "你听到「喀嚓」一声轻响，已被$N所发杀气挫伤，$n顿时血冒三丈！！！\n" NOR ]);

                return result;
        }
}

string perform_action_file(string action) 
{
        return __DIR__ + "lingxi-zhi-finger" + "/" + action; 
}