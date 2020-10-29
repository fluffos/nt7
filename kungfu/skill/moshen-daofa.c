// This program is a part of NITAN MudLIB

inherit SKILL;

mapping *action = ({
([      "action": "$N手中$w冒出阵阵寒气，“唰”地一声出奇不意地朝$n的$l劈来",
        "force" : 20,
        "dodge" : 10,
        "parry" : 25,
        "damage": 5,
        "lvl"   : 0,
        "skill_name"  : "停车问路",
        "damage_type" : "割伤"
]),
([      "action": "$N身形下沉，身子不住旋转，手中$w挽做一团刀花朝$n的$l处削去",
        "force" : 30,
        "dodge" : 30,
        "parry" : 40,
        "damage": 10,
        "lvl"   : 20,
        "skill_name"  : "童子挂画",
        "damage_type" : "割伤"
]),
([      "action": "$N手中$w一挥，招式大开大阖，只见瞬时万般刀光朝$n的$l处砍去",
        "force" : 40,
        "dodge" : 35,
        "parry" : 45,
        "damage": 15,
        "lvl"   : 40,
        "skill_name"  : "推窗望月",
        "damage_type" : "割伤"
]),
([      "action": "$N手中的$w略走偏锋，左转有弯，阴诡无比一招砍向$n的$l",
        "force" : 60,
        "dodge" : 45,
        "parry" : 45,
        "damage": 20,
        "lvl"   : 60,
        "skill_name"  : "开门见山",
        "damage_type" : "割伤"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("你的内力修为不够。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("moshen-daofa", 1))
                return notify_fail("你的基本刀法水平有限，无法领会更高深的魔神刀法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("moshen-daofa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的体力不够练魔神刀法。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的内力不够练魔神刀法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -43, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"moshen-daofa/" + action;
}