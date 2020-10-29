//pili-daofa.c 霹雳刀法

inherit SKILL;

mapping *action = ({
([      "action" : "$N发出一声厉吼，手中$w以一招「翻江搅海」，带着呼呼风声向$n的$l砍去",
        "force"  : 30,
        "attack" : 10,
        "dodge"  : 30,
        "parry"  : 20,
        "damage" : 20,
        "lvl"    : 0,
        "skill_name" : "翻江搅海",
        "damage_type" : "砍伤"
]),
([      "action":"$N舞动$w，使出「八方风雨」，幻出了无数$w向$n劈去。",
        "force" :45,
        "attack":22,
        "dodge" :40,
        "parry" :32,
        "damage":28,
        "lvl"   :20,
        "skill_name" :"八方风雨",
        "damage_type":"劈伤"
]),
([      "action":"$N大喝一声，一招「旋风骤起」，挥动$w快速击向$n$l。",
        "force" :60,
        "attack":34,
        "dodge" :53,
        "parry" :40,
        "damage":35,
        "lvl"   :50,
        "skill_name" :"旋风骤起",
        "damage_type":"割伤"
]),
([      "action":"$N俯身抢上，一记「揽月高塘」，$w直砍$n双腿。",
        "force" :80,
        "attack":50,
        "dodge" :70,
        "parry" :55,
        "damage":50,
        "lvl"   :90,
        "skill_name" :"揽月高塘",
        "damage_type":"砍伤"
]),
([      "action":"$N一招「斜阳疏影」，身形一跃，斜冲向前，右手挥动$w向下直斩$n的$l。",
        "force" :100,
        "attack":65,
        "dodge" :82,
        "parry" :68,
        "damage":65,
        "lvl"   :110,
        "skill_name" :"斜阳疏影",
        "damage_type":"砍伤"
]),
([      "action":"只见$N弓步上前，双手紧握$w，一招「凤凰展翼」，飞速击向$n的$l。",
        "force" :150,
        "attack":80,
        "dodge" :95,
        "parry" :80,
        "damage":80,
        "lvl"   :150,
        "skill_name" :"凤凰展翼",
        "damage_type":"割伤"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你必须手里拿着刀才能练刀法。\n");

        if ((int)me->query_skill("riyue-xinfa", 1) < 100)
                return notify_fail("你的内功心法火候太浅，不能学霹雳刀法。\n");

        if ((int)me->query_skill("blade", 1) < 80)
                return notify_fail("你的基本刀法火候不够。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的内力太低，无法学霹雳刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("pili-daofa", 1))
                return notify_fail("你的刀法水平有限，无法领会更高深的霹雳刀法。\n");

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
        int i, level;
        level = (int) me->query_skill("pili-daofa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力不够练霹雳刀法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够练霹雳刀法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -68, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pili-daofa/" + action;
}
