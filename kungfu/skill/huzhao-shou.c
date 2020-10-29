inherit SKILL;

mapping *action = ({
([      "action": "在呼呼风声中，$N使一招「虎口夺食」，双手如钩如戢，插向$n的$l",
        "force" : 60,
        "dodge" : 17,
        "parry" : 1,
        "damage": 1,
        "damage_type" : "抓伤",
        "skill_name" : "虎口夺食",
]),
([      "action": "$N身形一跃，费神扑上，使出一招「饿虎扑食」，右手直直抓向$n的$l",
        "force" : 80,
        "dodge" : 20,
        "parry" : 5,
        "damage": 3,
        "damage_type" : "抓伤",
        "skill_name" : "饿虎扑食",
]),
([      "action": "$N双手平伸，十指微微上下抖动，一招「山崩地裂」打向$n的$l",
        "force" : 120,
        "dodge" : 32,
        "parry" : 10,
        "damage": 5,
        "damage_type" : "抓伤",
        "skill_name" : "山崩地裂",
]),
([      "action": "$N使出一招「夜黑风高」，悄无声息的游走至$n身前，猛的一爪奋力抓向$n的$l",
        "force" : 132,
        "dodge" : 38,
        "parry" : 19,
        "damage": 5,
        "damage_type" : "抓伤",
        "skill_name" : "夜黑风高",
]),
([      "action": "$N双手平提胸前，左手护住面门，一招「损筋断骨」右手推向$n的$l",
        "force" : 137,
        "dodge" : 41,
        "parry" : 21,
        "damage": 7,
        "damage_type" : "抓伤",
        "skill_name" : "损筋断骨",
]),
([      "action": "$N使出「恶林虎啸」，低喝一声，双手化掌为爪，一前一后抓向$n的$l",
        "force" : 143,
        "dodge" : 49,
        "parry" : 22,
        "damage": 9,
        "damage_type" : "抓伤",
        "skill_name" : "恶林虎啸",
]),
([      "action": "$N使出「困兽犹斗」，双爪如狂风骤雨般对准$n的$l连续抓出",
        "force" : 151,
        "dodge" : 58,
        "parry" : 38,
        "damage": 15,
        "damage_type" : "抓伤",
        "skill_name" : "困兽犹斗",
])
});

string main_skill() { return "baihua-cuoquan"; }

int valid_learn(object me)
{
        if (me->query_skill("baihua-cuoquan", 1) > 0)
                return notify_fail("你已经练成了百花错拳，不必再单独学习了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练虎爪手必须空手。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("huzhao-shou", 1))
                return notify_fail("你的基本爪法火候不足，无法领会更高深的虎爪手。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "claw" || usage=="parry";
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("huzhao-shou",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你现在手足酸软，休息一下再练吧。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("qi", 80);
        addn("neili", -50, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huzhao-shou/" + action;
}
