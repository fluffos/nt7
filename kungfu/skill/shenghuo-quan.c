// shenghuo-quan.c
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N左拳虚晃，右拳若有若无悄然飞出，身形如同微风吹拂下的火焰，径直袭向$n",
        "force" : 100,
        "dodge" : 15,
        "parry" : 10,
        "lvl" : 0,
        "damage" : 20,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N双拳齐出，拳风呼啸，热浪阵阵，拳势直指$n的$l",
        "force" : 120,
        "dodge" : -20,
        "parry" : 20,
        "lvl" : 10,
        "damage" : 30,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N下身沉稳，上身却微伏向前，出拳飘忽，如闪烁的火焰般吞吐不定，无情的击向$n",
        "force" : 140,
        "dodge" : 30,
        "parry" : -20,
        "lvl" : 20,
        "damage" : 40,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N不进反退，轻轻一拳，出招虽然缓慢，但是炙热的劲气卷向$n的$l",
        "force" : 160,
        "dodge" : -50,
        "parry" : -10,
        "lvl" : 30,
        "damage" : 40,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N拳势大盛，如同风中的篝火，气焰升腾飘旋，$n只感觉热浪扑面，拳招从四面八方袭来",
        "force" : 180,
        "dodge" : -30,
        "parry" : 20,
        "lvl" : 40,
        "damage" : 50,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N面色凝重，一拳又一拳突然沉稳无比，虽是劈空而发，拳劲却如同火球直击$n的$l",
        "force" : 200,
        "dodge" : 50,
        "parry" : -30,
        "lvl" : 50,
        "damage" : 50,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身形急转，忽左忽右，忽前忽后，拳劲如同升腾的火焰直向$n招呼过去",
        "force" : 220,
        "dodge" : 10,
        "parry" : 10,
        "lvl" : 60,
        "damage" : 60,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N胸口空门大开，状似破绽，双拳却左右围合，夹带着滚滚热浪直击$n",
        "force" : 250,
        "dodge" : 40,
        "parry" : -10,
        "lvl" : 70,
        "damage" : 60,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N脸露诡异微笑，满面红光大盛，单拳击出，拳势凌厉，带着滔天热浪直向$n的$l扑去",
        "force" : 280,
        "dodge" : -30,
        "parry" : -20,
        "lvl" : 80,
        "damage" : 70,
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage == "cuff" ||  usage == "parry"; }

int valid_combine(string combo) { return combo=="guangming-zhang"; }

int valid_learn(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("练圣火拳必须空手。\n");

        if ((int)me->query_skill("cuff", 1) < 10)
                return notify_fail("你的基本拳法火候不够，无法练圣火拳。\n");


        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("shenghuo-quan", 1))
                return notify_fail("你的基本拳法水平有限，无法领会更高深的圣火拳。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("shenghuo-quan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)query("qi", me) < 60)
                return notify_fail("你的体力太低了。\n");

        if ((int)query("neili", me) < 70)
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("qi", 20);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shenghuo-quan/" + action;
}