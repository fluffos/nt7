//tianmo-shou.c 天魔手
//By haiyan

inherit SKILL;

mapping *action = ({
([      "action":"$N一招「覆雨翻云」，左手抓向$n的丹田，就在$n回身自防的一瞬间，右手却已掐上了$n的$l。",
        "force" :95,
        "attack":15,
        "parry" :10,
        "dodge" :30,
        "damage":20,
        "lvl"   :0,
        "skill_name" :"覆雨翻云",
        "damage_type":"瘀伤"
]),
([      "action":"$N双手一错，右手向外横推而出，一招「风起云涌」带着一股劲风拍向$n的$l。",
        "force" :120,
        "attack":28,
        "parry" :40,
        "dodge" :60,
        "damage":35,
        "lvl"   :50,
        "skill_name" :"风起云涌",
        "damage_type":"瘀伤"
]),
([      "action":"忽听$N一声怒吼，右手高高举起，一式「高山流水」，砍向$n的$l。",
        "force" :160,
        "attack":40,
        "parry" :70,
        "dodge" :90,
        "damage":53,
        "lvl"   :80,
        "skill_name" :"高山流水",
        "damage_type":"砍伤"
]),
([      "action":"$N身子微斜，随即跨出一步，左手忽掌忽爪使出「两处茫茫」，拍向$n的$l。",
        "force" :190,
        "attack":56,
        "parry" :100,
        "dodge" :120,
        "damage":70,
        "lvl"   :130,
        "skill_name" :"两处茫茫",
        "damage_type":"瘀伤"
]),
([      "action":"$N使出「出没风波里」，双手滑溜异常对准$n的$l抓去。",
        "force" :220,
        "attack":74,
        "parry" :130,
        "dodge" :150,
        "damage":90,
        "lvl"   :160,
        "skill_name" :"出没风波里",
        "damage_type":"抓伤"
]),
([      "action":"$N右手在$n$l划过，随后一招「捕风捉影」左手又向同一方位抓去。",
        "force" :260,
        "attack":100,
        "parry" :180,
        "dodge" :200,
        "damage":150,
        "lvl"   :200,
        "skill_name" :"捕风捉影",
        "damage_type":"抓伤"
]),
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练天魔手必须空手。\n");

        if ((int)me->query_skill("riyue-xinfa", 1) < 100)
                return notify_fail("你的内功心法火候太浅，不能学天魔手。\n");

        if ((int)me->query_skill("hand", 1) < 100)
                return notify_fail("你的基本手法火候不够。\n");

        if( query("max_neili", me)<350 )
                return notify_fail("你的内力太低，无法学天魔手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("tianmo-shou", 1))
                return notify_fail("你的基本手法水平有限，无法领会更高深的天魔手。\n");

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
        level = (int) me->query_skill("tianmo-shou", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练天魔手必须空手。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的体力不够练天魔手。\n");

        if( query("neili", me)<90 )
                return notify_fail("你的内力不够练天魔手。\n");

        me->receive_damage("qi", 85);
        addn("neili", -65, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianmo-shou/" + action;
}
