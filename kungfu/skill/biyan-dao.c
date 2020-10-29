inherit SKILL;

mapping *action = ({
([      "action" : "$N藏刀内收，一招「碧海青天」，刀锋自下而上划了个半弧，向$n的$l挥去",
        "force" : 10,
        "attack": 18,
        "dodge" : 1,
        "parry" : 5,
        "damage": 10,
        "lvl" : 0,
        "skill_name" : "碧海青天",
        "damage_type" : "割伤"
]),
([      "action" : "$N左掌虚托右肘，一招「碧玉丹心」，手中$w笔直划向$n的$l",
        "force" : 30,
        "attack": 16,
        "dodge" : 3,
        "parry" : 7,
        "damage": 12,
        "lvl" : 20,
        "skill_name" : "碧玉丹心",
        "damage_type" : "割伤"
]),
([      "action" : "$N一招「青烟缈缈」，$w绕颈而过，刷地一声自上而下向$n猛劈",
        "force" : 53,
        "attack": 19,
        "dodge" : 2,
        "parry" : 13,
        "damage": 17,
        "lvl" : 40,
        "skill_name" : "青烟缈缈",
        "damage_type" : "割伤"
]),
([      "action" : "$N右手反执刀柄，一招「烟碧三宵」，猛一挫身，$w直向$n的颈中斩去",
        "force" : 61,
        "attack": 27,
        "dodge" : 5,
        "parry" : 19,
        "damage": 25,
        "lvl" : 60,
        "skill_name" : "烟碧三宵",
        "damage_type" : "割伤",
]),
([      "action" : "$N一招「烟消云散」，无数刀尖化作点点繁星，向$n的$l挑去",
        "force" : 80,
        "attack": 52,
        "dodge" : 10,
        "parry" : 11,
        "damage": 30,
        "lvl" : 80,
        "skill_name" : "烟消云散",
        "damage_type" : "割伤"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的内功火候不到，无法学习碧烟刀法。\n");

        if( query("max_neili", me)<350 )
                return notify_fail("你的内力太差，无法学习碧烟刀法。\n");

        if ((int)me->query_skill("blade", 1) < 30)
                return notify_fail("你的基本刀法火候太浅，无法学习碧烟刀法。\n");

        if (me->query_skill("blade", 1) < me->query_skill("biyan-dao", 1))
                return notify_fail("你的基本刀法水平有限，无法领会更高深的碧烟刀法。\n");

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
        int d_e1 = 45;
        int d_e2 = 20;
        int p_e1 = -10;
        int p_e2 = -25;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 110;
        int m_e2 = 220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("biyan-dao", 1);
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
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "割伤" : "擦伤",
        ]);
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<40 )
                return notify_fail("你的体力不够练碧烟刀法。\n");

        if( query("neili", me)<30 )
                return notify_fail("你的内力不够练碧烟刀法。\n");

        me->receive_damage("qi", 35);
        addn("neili", -20, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"biyan-dao/" + action;
}