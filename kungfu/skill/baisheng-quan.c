inherit SKILL;

mapping *action = ({
([      "action": "$N马步一立，身子微曲，暗喝一声，一招「猫蹿」，一拳直捅$n的$l",
        "force" : 130,
        "dodge" : 5,
        "parry" : 7,
        "attack": 14,
        "damage": 4,
        "lvl"   : 0,
        "skill_name" : "猫蹿",
        "damage_type": "瘀伤"
]),
([      "action": "$N哈哈一笑，左拳由下至上，右拳平平击出，一招「兔滚」，交替打向$n",
        "force" : 145,
        "dodge" : 18,
        "parry" : 17,
        "attack": 16,
        "damage": 6,
        "lvl"   : 20,
        "skill_name" : "兔滚",
        "damage_type": "瘀伤"
]),
([      "action": "$N对$n一声大喝，使一招「鹰翻」，左拳击出，随即右拳跟上，两重力道打向$n的$l",
        "force" : 157,
        "dodge" : 16,
        "parry" : 19,
        "attack": 17,
        "damage": 11,
        "lvl"   : 40,
        "skill_name" : "鹰翻",
        "damage_type": "瘀伤"
]),
([      "action": "$N闷喝一声，双拳向上分开，一记「鹞子翻身」，拳划弧线，左右同时击向$n的$l",
        "force" : 165,
        "dodge" : 24,
        "parry" : 21,
        "attack": 19,
        "damage": 14,
        "lvl"   : 60,
        "skill_name" : "鹞子翻身",
        "damage_type": "瘀伤"
]),
([      "action": "$N施出「细胸巧」，一声大吼，一拳凌空打出，拳风直逼$n的$l",
        "force" : 185,
        "dodge" : 24,
        "parry" : 28,
        "attack": 33,
        "damage": 19,
        "lvl"   : 80,
        "skill_name" : "细胸巧",
        "damage_type": "瘀伤"
]),
([      "action": "$N一声长啸，双拳交错击出，一招「跺子脚」，拳风密布$n的前后左右",
        "force" : 197,
        "dodge" : 28,
        "parry" : 30,
        "attack": 36,
        "damage": 21,
        "lvl"   : 100,
        "skill_name" : "跺子脚",
        "damage_type": "瘀伤"
]),
([      "action": "$N怒吼一声，凌空飞起，一式「松子灵」，双拳居高临下，齐齐捶向$n",
        "force" : 285,
        "dodge" : 24,
        "parry" : 21,
        "attack": 47,
        "damage": 24,
        "lvl"   : 120,
        "skill_name" : "松子灵",
        "damage_type": "瘀伤"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练百胜神拳必须空手。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的内功火候不够，无法学百胜神拳。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的内力太弱，无法练百胜神拳。\n");

        if ((int)me->query_skill("cuff", 1) < 40)
                return notify_fail("你的基本拳脚火候太浅。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("baisheng-quan", 1))
                return notify_fail("你的基本拳脚水平有限，无法领会更高深的百胜神拳。\n");

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
        int d_e1 = 20;
        int d_e2 = 40;
        int p_e1 = -35;
        int p_e2 = 15;
        int f_e1 = 200;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("baisheng-quan", 1);
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

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你现在手足酸软，休息一下再练吧。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("qi", 50);
        addn("neili", -34, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baisheng-quan/" + action;
}