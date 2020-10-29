// This program is a part of NITAN MudLIB

inherit SKILL;

mapping *action = ({
([      "action" : "$N手中$w冒出阵阵寒气，“唰”地一声出奇不意地朝$n的$l刺来",
        "force"  : 120,
        "dodge"  : 20,
        "damage" : 25,
        "lvl"    : 0,
        "skill_name" : "飞燕入林",
        "damage_type": "刺伤"
]),
([      "action" : "$N身形下沉，身子不住旋转，手中$w挽做一团剑花朝$n的$l处削去",
        "force"  : 120,
        "dodge"  : 20,
        "damage" : 20,
        "lvl"    : 10,
        "skill_name" : "青龙吐水",
        "damage_type": "刺伤"
]),
([      "action" : "$N手中的$w略走偏锋，左转有弯，阴诡无比一招刺向$n的$l",
        "force"  : 140,
        "dodge"  : 15,
        "damage" : 25,
        "lvl"    : 20,
        "skill_name" : "凤凰挚窝",
        "damage_type": "刺伤"
]),
([      "action" : "$N手中$w一挥，剑式大开大阖，只见瞬时万般剑影朝$n的$l处刺来",
        "force"  : 150,
        "dodge"  : 15,
        "damage" : 35,
        "lvl"    : 30,
        "skill_name" : "玉女脱衣",
        "damage_type": "刺伤"
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("moshen-jianfa", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的魔神剑法。\n");

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
        int i, level;
        level = (int) me->query_skill("moshen-jianfa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<40 )
                return notify_fail("你的体力不够练魔神剑法。\n");

        if( query("neili", me)<10 )
                return notify_fail("你的内力不够练魔神剑法。\n");

        me->receive_damage("qi", 25);
        addn("neili", -10, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"moshen-jianfa/" + action;
}