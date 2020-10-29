// yujiamu-quan.c 金刚瑜迦母拳

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N并举双拳，使出一招"HIC"「灌顶」"NOR"，当头砸向$n的$l",
        "skill_name" : "灌顶",
        "lvl" : 0
]),
([        "action" : "$N使出一招"HIC"「解苦」"NOR"，身形一低，左手护顶，右手一拳击向$n的裆部",
        "skill_name" : "解苦",
        "lvl" : 8
]),
([        "action" : "$N使出一招"HIC"「颦眉」"NOR"，左拳虚击$n的前胸，一错身，右拳横扫$n的太阳穴",
        "skill_name" : "颦眉",
        "lvl" : 16
]),
([        "action" : "$N神形怪异，使一招"HIC"「嗔恚」"NOR"，双拳上下击向$n的$l",
        "skill_name" : "嗔恚",
        "lvl" : 24
]),
([        "action" : "$N使出一招"HIC"「静寂」"NOR"，双拳交错，缓缓击出，劲气直指$n的$l",
        "skill_name" : "静寂",
        "lvl" : 32
]),
([        "action" : "$N微微一笑，使出一式"HIC"「妙音」"NOR"，双拳前后击出，直取$n的左胸",
        "skill_name" : "妙音",
        "lvl" : 40
]),
([        "action" : "$N使出一招"HIC"「明心」"NOR"，全身疾转，双拳横扫$n的$l",
        "skill_name" : "明心",
        "lvl" : 48
]),
([        "action" : "$N飞身一跃，使出一招"HIC"「制胜」"NOR"，一拳猛击$n咽喉",
        "skill_name" : "制胜",
        "lvl" : 56
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }
int valid_combine(string combo)
{
        return combo=="dashou-yin" ||
               combo=="huoyan-dao";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练金刚瑜迦母拳必须空手。\n");

        if( query("max_neili", me)<600 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("yujiamu-quan",1))
                return notify_fail("你的基本拳法水平有限，无法领会更高深的金刚瑜迦母拳。\n");

        return 1;
}

int practice_skill(object me)
{
//      object weapon;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练金刚瑜迦母拳必须空手。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的体力不够，练不了金刚瑜迦母拳。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的内力不够练金刚瑜迦母拳。\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 30;
        int d_e2 = 55;
        int p_e1 = -25;
        int p_e2 = -10;
        int f_e1 = 100;
        int f_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("yujiamu-quan", 1);
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
                "damage_type" : "瘀伤",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
       return __DIR__"yujiamu-quan/" + action;
}

int help(object me)
{
        write(HIC"\n金刚瑜迦母拳："NOR"\n");
        write(@HELP

    金刚瑜迦母拳是密宗雪山寺武功。
    可与密宗大手印互备。

        学习要求：
                龙象般若功或小无相功20级
                内力50
HELP
        );
        return 1;
}