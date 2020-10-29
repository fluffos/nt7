// This is player's own skill (Write by Lonely@nt2)
// Create by 剑人(Dlf) at Fri Feb 27 13:27:06 2015
// 龙凤剑(longfeng-sword.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N纵身一跃，手握$w,顿时一招「临」对准$n的$l斜斜刺出一剑",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "刺伤",
	"skill_name" : "临"
 ]),
// ZHAOSHI : 1
([      "action" : "HIW\n忽然间$NHIW身形猛转，刹时狂风如潮，遮云蔽日，天地为之变色，这正是《龙凤剑谱》所记载绝学「HIR兵式HIW」。转眼间$NHIW已不见了踪影，只听得一声尖啸，一道白光从天而下将$nHIW笼罩！NOR",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 110,
	"damage_type" : "刺伤",
	"skill_name" : "兵"
 ]),
// ZHAOSHI : 2
([      "action" : "$N身形一转，一招「斗」$w剑光不定，斩向$n",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 120,
	"damage_type" : "刺伤",
	"skill_name" : "斗"
 ]),
// ZHAOSHI : 3
([      "action" : "$N舞动$w，一招「者」迅捷无伦地劈向$n",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 130,
	"damage_type" : "刺伤",
	"skill_name" : "者"
 ]),
// ZHAOSHI : 4
([      "action" : "$N提剑过肩，蓄劲发力，一招「皆」直劈$n",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 140,
	"damage_type" : "刺伤",
	"skill_name" : "皆"
 ]),
// ZHAOSHI : 5
([      "action" : "$N移步侧身，使一招「阵」剑光霍霍斩向$n",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 150,
	"damage_type" : "刺伤",
	"skill_name" : "阵"
 ]),
// ZHAOSHI : 6
([      "action" : "$N金刃劈风，$w随著一招「腾蛟起风」由下而上撩往$n",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 160,
	"damage_type" : "刺伤",
	"skill_name" : "列"
 ]),
// ZHAOSHI : 7
([      "action" : "$N突然跃起丈余，$n一抬头，发现空中并无$N的身影，而一股寒气却从后袭来。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 180,
	"damage_type" : "刺伤",
	"skill_name" : "在"
 ]),
// ZHAOSHI : 8
([      "action" : "$N一声冷笑，一招「前」蓦地里疾冲上前，当真是动如脱兔，一瞬之间，与$n相距已不到一尺，两人的鼻子几乎要碰在一起。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 200,
	"damage_type" : "刺伤",
	"skill_name" : "前"
 ]),
// ZHAOSHI : 9
});

int valid_learn(object me)
{
        object weapon; 
        
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
                
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练" + "龙凤剑" + "。\n");
                
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
        level = (int)me->query_skill("longfeng-sword",1);
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

        lvl = me->query_skill("longfeng-sword", 1);
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
        return __DIR__ + "longfeng-sword" + "/" + action; 
}