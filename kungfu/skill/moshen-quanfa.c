inherit SKILL;

mapping *action = ({
([      "action": "$N腰一闪，挥起左拳朝$n的$l处打去",
        "force" : 60,
        "attack": 20,
        "dodge" : 40,
        "parry" : 5,
        "damage": 6,
        "lvl"   : 0,
        "skill_name" : "冲天炮",
        "damage_type":  "砸伤"
]),
([      "action": "$N身形往后一退，气沉丹田，双拳猛地朝$n的$l处打去",
        "force" : 80,
        "attack": 25,
        "dodge" : 43,
        "parry" : 6,
        "damage": 7,
        "lvl"   : 30,
        "skill_name" : "拔草寻蛇",
        "damage_type":  "瘀伤"
]),
([      "action": "$N纵身跃起，双腿一扫，接着一个跟斗，右拳猛地朝$n的$l处打来",
        "force" : 100,
        "attack": 28,
        "dodge" : 45,
        "parry" : 8,
        "damage": 10,
        "lvl"   : 60,
        "skill_name" : "叶底偷桃",
        "damage_type":  "抓伤"
]),
([      "action": "$N左拳攻向$n面部，同时右拳朝$n的$l处用力打去",
        "force" : 120,
        "attack": 35,
        "dodge" : 47,
        "parry" : 11,
        "damage": 17,
        "lvl"   : 80,
        "skill_name" : "黑虎掏心",
        "damage_type":  "瘀伤"
]),
});

int valid_enable(string usage)
{
        return usage == "cuff" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练魔神拳法必须空手。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的内力不够，无法练习魔神拳法法。\n");

        if ((int)me->query_skill("cuff", 1) < 20)
                return notify_fail("你的基本拳法火候太浅。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("moshen-quanfa", 1))
                return notify_fail("你的基本拳法火候有限，无法领会更高深的魔神拳法法。\n");

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
        level = (int)me->query_skill("moshen-quanfa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你现在手足酸软，休息一下再练吧。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("qi", 65);
        addn("neili", -40, me);

        return 1;
}