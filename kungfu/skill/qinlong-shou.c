inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "在呼呼风声中，$N飞身一跃，双手如钩如戢，插向$n的$l",
        "force" : 60,
        "dodge" : 20,
        "parry" : 35,
        "damage": 35,
        "damage_type" : "抓伤"
]),
([      "action": "$N双手平提胸前，左手护住面门，右手猛然抓向$n的$l",
        "force" : 137,
        "dodge" : 41,
        "parry" : 21,
        "damage": 40,
        "damage_type" : "抓伤"
]),
([      "action": "$N低喝一声，双手化掌为爪，一前一后抓向$n的$l",
        "force" : 143,
        "dodge" : 49,
        "parry" : 22,
        "damage": 90,
        "damage_type" : "抓伤"
]),
([      "action": "$N跨前一步，双爪如狂风骤雨般对准$n的$l连续抓出",
        "force" : 151,
        "dodge" : 58,
        "parry" : 38,
        "damage": 150,
        "damage_type" : "抓伤"
])
});

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练擒龙手手必须空手。\n");
        
        if ( me->query_skill("hand", 1) < 80)
               return notify_fail("你的基本手法不够。\n");                

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("qinlong-shou", 1))
                return notify_fail("你的基本手法火候不足，无法领会更高深的擒龙手。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "hand" || usage=="parry";
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
        return __DIR__"qinlong-shou/" + action;
}
