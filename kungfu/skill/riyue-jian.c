// riyue-jian.c 日月剑法

inherit SKILL;

mapping *action = ({
([      "action" : "$N手中$w上挑刺向$n。",
        "force"  : 120,
        "dodge"  : 20,
        "damage" : 30,
        "lvl"    : 0,
        "damage_type": "刺伤"
]),
([      "action" : "$N一挽手中$w，剑尖斜斜地向$n的$l挥去。",
        "force"  : 120,
        "dodge"  : 20,
        "damage" : 35,
        "lvl"    : 10,
        "damage_type": "刺伤"
]),
([      "action" : "只见$N手中$w闪出点点剑光，连成一线，刺向$n的脸部。",
        "force"  : 140,
        "dodge"  : 15,
        "damage" : 40,
        "lvl"    : 10,
        "damage_type": "刺伤"
]), 
([      "action" : "$N碎步急进，提剑沿剑身方向疾速上崩，一招「白蛇吐信」直取$n的$l",
        "force"  : 150,
        "dodge"  : 15,
        "damage" : 45,
        "lvl"    : 30,
        "damage_type": "刺伤"
]),
([      "action" : "只见$N舞动手中$w,从一个意想不到的角度突然挑出一剑，向$n的$l直刺。",
        "force"  : 130,
        "dodge"  : 25,
        "damage" : 45,
        "lvl"    : 40,
        "damage_type": "刺伤"
]),
([      "action" : "$N手臂往前一伸，$w向$n急刺过去。",
        "force"  : 120,
        "dodge"  : 25,
        "damage" : 50,
        "lvl"    : 50,
        "damage_type": "刺伤"
]),
([      "action" : "$N手拿$w，向$n的$l飞速一击。",
        "force"  : 110,
        "dodge"  : 15,
        "damage" : 70,
        "lvl"    : 60,
        "damage_type": "刺伤"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
    object ob;

    if( query("max_neili", me)<100 )
        return notify_fail("你的内力不够。\n");

    if ((int)me->query_skill("force") < 20)
        return notify_fail("你的内功火候太浅。\n");

    if( !objectp(ob=query_temp("weapon", me) )
        || query("skill_type", ob) != "sword" )
        return notify_fail("你必须先找一把剑才能学习剑法。\n"); 

    if ((int)me->query_skill("sword", 1) < (int)me->query_skill("riyue-jian", 1))
        return notify_fail("你的基本剑法水平有限，无法领会更高深的日月剑法。\n");

    return 1;
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level = (int) me->query_skill("riyue-jian", 1);
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
          return notify_fail("你的体力不够练日月剑法。\n");

    if( query("neili", me)<10 )
          return notify_fail("你的内力不够练日月剑法。\n");

    me->receive_damage("qi", 25);
    addn("neili", -10, me);

    return 1;
}
