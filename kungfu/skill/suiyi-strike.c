// This is player's own skill (Write by Lonely@nt2)
// Create by 了尽(Zxahh) at Thu Feb 26 21:57:20 2015
// 随意掌(suiyi-strike.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N突然如同放弃了所有武学招式随意而动，脚步悠然一如踏青而行，却瞬间出现在$n面前，$n还没反应过来，便被一巴掌摔倒了脸上！",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "内伤",
	"skill_name" : "随意而为"
 ]),
// ZHAOSHI : 1
([      "action" : "$N忽如消失一般，$n定神一看，不知何时$N已经出现在身后，无论如何也无法逃脱，$n惊恐之下被$N一掌拍中了后脑勺",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 110,
	"damage_type" : "内伤",
	"skill_name" : "如影相随"
 ]),
// ZHAOSHI : 2
([      "action" : "$N暮然回身背对这$n，让$n不由一愣，咋时$N一个进步后跨，后肘击中了$n的胸口！",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 120,
	"damage_type" : "内伤",
	"skill_name" : "意想不到"
 ]),
// ZHAOSHI : 3
([      "action" : "$N灵机一发，身体已经一步跨到了$n的面前，一掌拍向了$n的天灵盖",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 130,
	"damage_type" : "内伤",
	"skill_name" : "身随意动"
 ]),
// ZHAOSHI : 4
([      "action" : "$N两臂如鹏翼般挥动，一股强大的内力犹如飓风拍在了$n的胸口，是$n的内府具碎！",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 140,
	"damage_type" : "内伤",
	"skill_name" : "一切随风"
 ]),
// ZHAOSHI : 5
([      "action" : "$N怒喝一声，$n只觉一声惊雷在脑中响起，还没回过神来，$N已经伴随喝声出现在$n面前，一掌拍在了$n心脉之上！",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 150,
	"damage_type" : "内伤",
	"skill_name" : "言出法随"
 ]),
// ZHAOSHI : 6
([      "action" : "$n看到$N露出了破绽正欲进攻，$N突然一个扭动破绽居然消失无踪，一招杀招出现其中！",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 160,
	"damage_type" : "内伤",
	"skill_name" : "出其不意"
 ]),
// ZHAOSHI : 7
([      "action" : "$N一跃而起，一掌上而下推出，巨大的掌压若天意般压下",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 180,
	"damage_type" : "内伤",
	"skill_name" : "一意动天"
 ]),
// ZHAOSHI : 8
([      "action" : "$N绕着$n转了一圈，$n没感觉有任何异样，突然之间感觉身体内一阵波动，确实几十重内劲同时爆发了！",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 200,
	"damage_type" : "内伤",
	"skill_name" : "逍遥随意"
 ]),
// ZHAOSHI : 9
});

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练"+"随意掌"+"必须空手。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练"+"随意掌"+"。\n");
        return 1;
}

int valid_enable(string usage) { 
        return usage == "strike" || 
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
        level = (int)me->query_skill("suiyi-strike",1);
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

        lvl = me->query_skill("suiyi-strike", 1);
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
        return __DIR__ + "suiyi-strike" + "/" + action; 
}