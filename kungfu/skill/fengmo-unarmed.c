// This is player's own skill (Write by Lonely@nt2)
// Create by 周不通(Butong) at Thu May 28 17:23:54 2015
// 疯魔拳(fengmo-unarmed.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N看上去半疯不癫，一脸傻笑，脚步不稳，却忽然一式「仙人摘桃」，自下而上往$n裆下一抓。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "瘀伤",
	"skill_name" : "半疯不癫"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练"+"疯魔拳"+"必须空手。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练"+"疯魔拳"+"。\n");
        return 1;
}

int valid_enable(string usage) { 
        return usage == "unarmed" || 
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
        level = (int)me->query_skill("fengmo-unarmed",1);
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

        lvl = me->query_skill("fengmo-unarmed", 1);
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
        return __DIR__ + "fengmo-unarmed" + "/" + action; 
}
string query_description()
{
	return
 "这套疯魔拳法，乃是全真教高人周不通疯狂时所创，招式威猛无比，快比
迅雷，拳如流星，一旦发狂以后千人也难以匹敌，万夫莫当。当年周不通
以这套疯魔拳打高处不胜寒，掌劈红莲老祖。连网游始祖也被一拳打倒在
泥潭。" ; 
}
