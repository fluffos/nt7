// This is player's own skill (Write by Lonely@nt2)
// Create by 星云锁链(Fuyuan) at Tue Mar  3 00:40:31 2015
// 野球拳(yeqiu-unarmed.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N俯首沉腰，身形一闪，跃到$n身后，一式「老汉推车」，两手死死的揪住$n的脚脖子，然后用力向上一提，往前一抖扔进前面的臭水沟里。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "瘀伤",
	"skill_name" : "老汉推车"
 ]),
// ZHAOSHI : 1
([      "action" : "$N飞身跃起，空中一个盘旋，一式「枯树盘根」，双腿死死锁住$n的脖子，然后用力一扭……",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 110,
	"damage_type" : "瘀伤",
	"skill_name" : "枯树盘根"
 ]),
// ZHAOSHI : 2
([      "action" : "$N嘎嘎怪笑，团身钻入$n裆下，口中喝到，看我「鸡飞蛋打」，挥拳狠狠向上捣去。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 120,
	"damage_type" : "瘀伤",
	"skill_name" : "鸡飞蛋打"
 ]),
// ZHAOSHI : 3
([      "action" : "$N纵身一个空翻，从$n头顶跃过，落地时顺势在$n屁股蛋子上狠狠踹了一脚，$n一个标准的「平沙落雁」姿势摔了个马趴。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 130,
	"damage_type" : "瘀伤",
	"skill_name" : "平沙落雁"
 ]),
// ZHAOSHI : 4
([      "action" : "$N噼啦噼啦对着自己的屁股一顿猛捶，$n微一愣神，被$N近身伸出食指一式「姜太公钓鱼」穿进鼻孔，顿时鼻血喷涌而出。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 140,
	"damage_type" : "瘀伤",
	"skill_name" : "姜太公钓鱼"
 ]),
// ZHAOSHI : 5
([      "action" : "$N念念叨叨，作「小和尚念经」状，左手虚握胸前防御，右手抽风般只把$n的脑门当做木鱼死命猛敲。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 150,
	"damage_type" : "瘀伤",
	"skill_name" : "小和尚念经"
 ]),
// ZHAOSHI : 6
([      "action" : "$n俯身向$N的下三路发起进攻，$N鱼跃闪过，顺势一式「乌云盖顶」，屁股狠狠的坐在$n头上。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 160,
	"damage_type" : "瘀伤",
	"skill_name" : "乌云盖顶"
 ]),
// ZHAOSHI : 7
([      "action" : "$N突然双脚静止不动，上身大幅旋转，$n一不留神立马中招，晕乎乎被这招「大风车」旋飞出去。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 180,
	"damage_type" : "瘀伤",
	"skill_name" : "大风车"
 ]),
// ZHAOSHI : 8
([      "action" : "$N气贯头顶，对$n的进攻不管不顾，一式「老和尚撞钟」，直往$n的胸口撞去。",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 200,
	"damage_type" : "瘀伤",
	"skill_name" : "老和尚撞钟"
 ]),
// ZHAOSHI : 9
});

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练"+"野球拳"+"必须空手。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太弱，无法练"+"野球拳"+"。\n");
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
        level = (int)me->query_skill("yeqiu-unarmed",1);
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

        lvl = me->query_skill("yeqiu-unarmed", 1);
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
        return __DIR__ + "yeqiu-unarmed" + "/" + action; 
}