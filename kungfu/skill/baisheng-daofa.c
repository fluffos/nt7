inherit SKILL;

mapping *action = ({
([      "action" : "$N手持$w一刀劈下，迅即无比，势不可当",
        "force"  : 210,
        "dodge"  : 20,
        "parry"  : 25,
        "lvl"    : 0,
        "damage" : 44,
        "damage_type" : "割伤",
]),
([      "action" : "$N刀锋自下而上划了个半弧，$w忽深忽吐，刺向$n的颈部",
        "force"  : 250,
        "dodge"  : 30,
        "parry"  : 40,
        "lvl"    : 25,
        "damage" : 51,
        "damage_type" : "割伤",
]),
([      "action" : "$N忽然将$w舞得天花乱坠，闪电般压向$n",
        "force"  : 270,
        "dodge"  : 35,
        "parry"  : 50,
        "lvl"    : 50,
        "damage" : 56,
        "damage_type" : "割伤",
]),
([      "action" : "$N一横$w，刀锋像门板一样向$n推去，封住$n所有的退路",
        "force"  : 280,
        "dodge"  : 45,
        "parry"  : 55,
        "lvl"    : 70,
        "damage" : 62,
        "damage_type" : "内伤",
]),
([      "action" : "$N转身跃起，手舞$w，身与刀进合做一道电光射向$n",
        "force"  : 305,
        "dodge"  : 50,
        "parry"  : 75,
        "lvl"    : 90,
        "damage" : 70,
        "damage_type" : "割伤",
]),
([      "action" : "$N挥舞$w，乱砍乱杀，$w化作道道白光，上下翻飞罩向$n",
        "force"  : 330,
        "dodge"  : 55,
        "parry"  : 85,
        "lvl"    : 110,
        "damage" : 75,
        "damage_type" : "割伤",
]),
([      "action" : "$N将$w使得毫无章法，不守半点规矩，偏生快得出奇，$w挟风声劈向$n的$l",
        "force"  : 350,
        "dodge"  : 52,
        "parry"  : 90,
        "lvl"    : 130,
        "damage" : 80,
        "damage_type" : "割伤",
]),
([      "action" : "$N大喝一声，手中的$w就如长虹一般向$n直劈而下",
        "force"  : 380,
        "dodge"  : 61,
        "parry"  : 95,
        "lvl"    : 150,
        "damage" : 85,
        "damage_type" : "割伤",
]),
});

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<600 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("blade", 1) < 60)
                return notify_fail("你的基本刀法火候不够，无法学习百胜刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("baisheng-daofa", 1))
                return notify_fail("你的基本刀法水平有限，无法领会更高深的百胜刀法。\n");

        return 1;
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

        lvl = (int)me->query_skill("baisheng-daofa", 1);
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

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力不够，练不了百胜刀法。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的内力不够，练不了百胜刀法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -68, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baisheng-daofa/" + action;
}