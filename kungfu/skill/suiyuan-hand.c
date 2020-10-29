// This is player's own skill (Write by Lonely@nt2)
// Create by 了尽(Zxahh) at Fri Feb 27 22:01:53 2015
// 随缘手(suiyuan-hand.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N双眼闭合，一手挥出，一切随缘，却不知为何一手按在了$n的心门上",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "瘀伤",
	"skill_name" : "一切随缘"
 ]),
// ZHAOSHI : 1
([      "action" : "$N神色黯然，口中轻轻念着“君生我未生”，不知如何出现在了$n面前，手已经按在了$n的胸口。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 110,
	"damage_type" : "瘀伤",
	"skill_name" : "君生我未生"
 ]),
// ZHAOSHI : 2
([      "action" : "$n定神一看，$N已经从眼前消失，“我生君已老”忽然在$N脑后响起，$n感毛骨悚然之时一股诡异内力从背后入侵攻入心脉！",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 120,
	"damage_type" : "瘀伤",
	"skill_name" : "我生君已老"
 ]),
// ZHAOSHI : 3
([      "action" : "$n正欲抢攻，但是这时$N整个人却突然陷入了哀怨之中，口中喃喃念道“君恨我生迟”,让$n迟疑了一下，下一刻$N的手轻轻的拂过了$n",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 130,
	"damage_type" : "瘀伤",
	"skill_name" : "君恨我生迟"
 ]),
// ZHAOSHI : 4
([      "action" : "$N突然面露狰狞，滔天恨意冲冠而起，不顾一切的一掌拍向了$n！",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 140,
	"damage_type" : "瘀伤",
	"skill_name" : "我恨君生早"
 ]),
// ZHAOSHI : 5
([      "action" : "$N忽然化作了一只彩蝶飞过了$n的身边，$n的耳中才留下了一句“化蝶去寻花”",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 150,
	"damage_type" : "瘀伤",
	"skill_name" : "化蝶去寻花"
 ]),
// ZHAOSHI : 6
([      "action" : "原本晃晃日光，但是$n的眼前如同陷入了黑夜，周围被一片小草所包围，芳草抚动中一声似有似无的声音传来，“夜夜栖芳草”。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 160,
	"damage_type" : "瘀伤",
	"skill_name" : "夜夜栖芳草"
 ]),
// ZHAOSHI : 7
([      "action" : "“只叹缘难成”$N神色黯然的说道，手如同别离般轻轻挥动，一股柔和的内力拂过了$n。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 180,
	"damage_type" : "瘀伤",
	"skill_name" : "只叹缘难成"
 ]),
// ZHAOSHI : 8
([      "action" : "$N的手仿佛越过了空间抵达$n的胸前，口中呢喃着“只愿来生缘”一句。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 200,
	"damage_type" : "瘀伤",
	"skill_name" : "只愿来生缘"
 ]),
// ZHAOSHI : 9
});

int valid_learn(object me)
{
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练"+"随缘手"+"。\n");
        return 1;
}

int valid_enable(string usage) { 
        return usage == "hand" || 
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
        level = (int)me->query_skill("suiyuan-hand",1);
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

        lvl = me->query_skill("suiyuan-hand", 1);
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
        return __DIR__ + "suiyuan-hand" + "/" + action; 
}