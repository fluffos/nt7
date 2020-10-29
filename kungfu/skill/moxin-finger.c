// This is player's own skill (Write by Lonely@nt2)
// Create by 枯枝(Kuzhi) at Sun May 24 23:17:30 2015
// 魔心十劫指(moxin-finger.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N挥指横扫，如魔行道，一式「魔道横行」，自空中往$n的头顶旋转而至，凡过之处，全无生机可存。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "瘀伤",
	"skill_name" : "魔道横行"
 ]),
// ZHAOSHI : 1
([      "action" : "$N十指连环弹动，尽封$n七个大穴，使其难以动弹，最后以十成功力的一指更是如流星一样而来。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 110,
	"damage_type" : "瘀伤",
	"skill_name" : "魔踏七星"
 ]),
// ZHAOSHI : 2
([      "action" : "只见$N以劲隔空御力，一片天下苍生在苦海沉浮，混乱颠倒，自相攻伐之象袭向$n。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 120,
	"damage_type" : "瘀伤",
	"skill_name" : "魔随空生"
 ]),
// ZHAOSHI : 3
([      "action" : "$N右臂紧伸，五指齐出，情未断，路先断，蕴含的魔气直逼$n，气势逼人无比。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 130,
	"damage_type" : "瘀伤",
	"skill_name" : "魔生情断"
 ]),
// ZHAOSHI : 4
([      "action" : "万劫浮生，是由怨怒推动的力量。只见$N指锋急劲，削向四周空气，产生了鬼泣的声音。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 140,
	"damage_type" : "瘀伤",
	"skill_name" : "群魔乱舞"
 ]),
// ZHAOSHI : 5
([      "action" : "只见从$N体内散出的阵阵魔气，伴随着无敌的气势攻向$n。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 150,
	"damage_type" : "瘀伤",
	"skill_name" : "魔气纵横"
 ]),
// ZHAOSHI : 6
([      "action" : "这是$N包含苍生对受神佛玩弄命运的仇恨反击，抛弃一切，破天灭神，一怒断佛，袭向$n。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 160,
	"damage_type" : "瘀伤",
	"skill_name" : "魔梵般若"
 ]),
// ZHAOSHI : 7
([      "action" : "只见$N悬浮半空，入魔乃至屠去七情，魔更为魔，此招出后$n已无幸存之望。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 180,
	"damage_type" : "瘀伤",
	"skill_name" : "魔极屠情"
 ]),
// ZHAOSHI : 8
([      "action" : "见血就会爆发屠杀的欲望，$N十指连戳，伴随着魔劲，攻敌至亡。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 200,
	"damage_type" : "瘀伤",
	"skill_name" : "血屠魔功"
 ]),
// ZHAOSHI : 9
});

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练"+"魔心十劫指"+"必须空手。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练"+"魔心十劫指"+"。\n");
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
        level = (int)me->query_skill("moxin-finger",1);
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

        lvl = me->query_skill("moxin-finger", 1);
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
        return __DIR__ + "moxin-finger" + "/" + action; 
}