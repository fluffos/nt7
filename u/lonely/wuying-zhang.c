//wuying-zhang 无影穿心掌

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N聚气凝神，$w忽然猛地一掌击向$n的$l，正是一招「天外飞影」！",
        "skill_name" : "天外飞影",
        "lvl" : 10
]),
([        "action" : "$N身行突然暴起，一招「无影飞击」以快速无比的速度拍向$n的$l处！",
        "skill_name" : "无影飞击",
        "lvl" : 15
]),
([        "action" : "$N左晃右闪，令人琢磨不定，一招「无影无踪」突然一掌打向$n的$l！",
        "skill_name" : "无影无踪",
        "lvl" : 20
]),
([        "action" : "$N的右手忽然化做万千掌影，从四面八方击向$n的$l，正是一招「千抚寻命」！",
        "skill_name" : "千抚寻命",
        "lvl" : 25
]),
([        "action" : "$N左掌拍向$n，突然身行猛地一转，绕到$n身后，右掌一招「幽影夺命」向$l拍了过去！",
        "skill_name" : "幽影夺命",
        "lvl" : 30
]),
([        "action" : "$N手中划出一个个的圈子，这招「天方地园」一出，顿时裹得$n眼花缭乱，不知所措！",
        "skill_name" : "天方地圆",
        "lvl" : 50
]),
([        "action" : HIR"$N左掌$w连劈数下，身行向前，右掌却一招[探囊取物]直劈向$n的$l！",
        "skill_name" : "探囊取物",
        "lvl" : 70
]),
([        "action" : "$N体内的真气在不断变化，不断游移，突然一招「无影匿斩」斩向$n的$l!",
        "skill_name" : "无影匿斩",
        "lvl" : 80
]),
([        "action" : "$N展身虚步，提腰跃落，一招「月夜疏影」，双掌一转，疾风般拍向$n！",
        "skill_name" : "月夜疏影",
        "lvl" : 90
]),
([        "action" : "HIB"$N身行诡异，闪动于$n的四周，猛地右掌成刀，使出一招[无影穿心]刺向$n的左胸!"NOR,
        "skill_name" : "无影穿心",
        "lvl" : 100
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry" ; }
int valid_combine(string combo) { return combo == "boyun-suowu"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练无影穿心掌必须空手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功火候不够，无法练无影穿心掌。\n");

        if( query("max_neili", me)<750 )
                return notify_fail("你的内力太弱，无法练无影穿心掌。\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("你的基本掌法火候不够，无法练习无影穿心掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("wuying-zhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的无影穿心掌。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手才能练习。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的内力不够练无影穿心掌。\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -35;
        int d_e2 = -5;
        int p_e1 = 5;
        int p_e2 = 35;
        int f_e1 = 170;
        int f_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("wuying-zhang", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 获得招数序号上限 */
                        break;
                }
        seq = random(seq);       /* 选择出手招数序号 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "内伤" : "瘀伤",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"wuying-zhang/" + action;
}
