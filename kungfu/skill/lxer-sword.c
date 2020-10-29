// This is player's own skill (Write by Lonely@nt2)
// Create by 风林火山(Lxer) at Sat May 16 22:29:05 2015
// 风林火山剑(lxer-sword.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N左挠右挠，在腋窝搓一把污泥抹在$w顶端,斜刺一招「苍松迎客」对准$n馋涎欲滴的大嘴送去",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "刺伤",
	"skill_name" : "风林"
 ]),
// ZHAOSHI : 1
([      "action" : "$N挠了再挠，从脚底板上扣下来一块污泥涂在$w上,顿时一招「臭气熏天」散发无穷威力,对准$n的胸口斜斜刺出一剑",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 110,
	"damage_type" : "刺伤",
	"skill_name" : "火山"
 ]),
// ZHAOSHI : 2
([      "action" : "$N身如鬼魅，手握$w,顿时一招「疾如风」对准$n的颈部斩落",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 120,
	"damage_type" : "刺伤",
	"skill_name" : "疾如风"
 ]),
// ZHAOSHI : 3
([      "action" : "$N严阵以待，手握$w,沉稳使出「徐如林」将$n暴风骤雨般的攻击格挡回去",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 130,
	"damage_type" : "刺伤",
	"skill_name" : "徐如林"
 ]),
// ZHAOSHI : 4
([      "action" : "$N一声怒吼，双手紧攥$w,向前猛力挥舞，一招「侵略如火」汹涌直冲$n的上身要害攻击",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 140,
	"damage_type" : "刺伤",
	"skill_name" : "侵掠如火"
 ]),
// ZHAOSHI : 5
([      "action" : "$N凝神静气，双手紧握$w,对$n的所有障眼法全都不管不顾，只管使出「不动如山」对敌",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 150,
	"damage_type" : "刺伤",
	"skill_name" : "不动如山"
 ]),
// ZHAOSHI : 6
});

int valid_learn(object me)
{
        object weapon; 
        
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
                
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练" + "风林火山剑" + "。\n");
                
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
        level = (int)me->query_skill("lxer-sword",1);
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

        lvl = me->query_skill("lxer-sword", 1);
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
        return __DIR__ + "lxer-sword" + "/" + action; 
}