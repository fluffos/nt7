#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action": "$N使一招「云里乾坤」，右拳至左拳之底穿出，对准$n$l猛然攻去",
        "force" : 50,
        "dodge" : 20,
        "parry" : 20,
        "attack": 15,
        "damage": 20,
        "lvl"   : 0,
        "skill_name" : "云里乾坤",
        "damage_type": "瘀伤"
]),
([      "action": "$N左拳突然张开，拳开变掌，一招「雾里看花」便往$n的$l招呼过去",
        "force" : 65,
        "dodge" : 25,
        "parry" : 25,
        "attack": 17,
        "damage": 23,
        "lvl"   : 20,
        "skill_name" : "雾里看花",
        "damage_type":  "瘀伤"
]),
([      "action": "$N两手虎口相对，往内一圈，一招「金鼓齐鸣」往$n的$l击出",
        "force" : 85,
        "dodge" : 31,
        "parry" : 33,
        "attack": 21,
        "damage": 28,
        "lvl"   : 40,
        "skill_name" : "金鼓齐鸣",
        "damage_type":  "瘀伤"
]),
([      "action": "$N步履一沉，左拳虚晃一招，右拳使出「梅花弄影」击向$n$l",
        "force" : 110,
        "dodge" : 42,
        "parry" : 45,
        "attack": 35,
        "damage": 33,
        "lvl"   : 60,
        "skill_name" : "梅花弄影",
        "damage_type":  "瘀伤"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_combine(string combo)
{
        return combo == "huashan-zhang";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练华山拳法必须空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的内功火候不够，无法学华山拳法。\n");

        if ((int)me->query_skill("cuff", 1) < 20)
                return notify_fail("你的基本拳法火候太浅。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("huashan-quan", 1))
                return notify_fail("你的基本拳法水平有限，无法领会更高深的华山拳法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
            if (level >= action[i]["lvl"])
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 40;
        int d_e2 = 60;
        int p_e1 = -20;
        int p_e2 = 0;
        int f_e1 = 100;
        int f_e2 = 200;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("huashan-quan", 1);
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

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够练华山拳法。\n");

        me->receive_damage("qi", 55);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huashan-quan/" + action;
}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n华山拳法："NOR"\n");
        write(@HELP

    华山拳法为华山气宗拳法。

        学习要求：
           紫霞10级
HELP
        );
        return 1;
}
