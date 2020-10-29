#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *action_msg = ({
        "$N左手扬起，右手伸出，五指曲张，对着$n的颈部便抓",
        "只见一阵劲风直逼向前$N单臂伸出，手指直取$n的哽嗓咽喉",
        "$N左手一掠，将$n防守招数尽格在外门，右手疾探而出对$n的喉头抓到",
        "$N身形急跳，早落到$n的身后，一双冰冷的大手抓向$n的后颈",
        "$N双臂弯出，柔若无骨，如两条软鞭一般，紧紧缠住$n的脖子不放",
});

mapping *action = ({
([      "action": "$N一声暴喝，双手如钩如戢，插向$n的$l",
        "force" : 100,
        "attack": 28,
        "dodge" : 17,
        "parry" : 0,
        "damage": 13,
        "lvl"   : 0,
        "damage_type" : "抓伤"
]),
([      "action": "$N身形一跃，直扑而上，右手直直抓向$n的$l",
        "force" : 130,
        "attack": 35,
        "dodge" : 20,
        "parry" : 5,
        "damage": 20,
        "lvl"   : 10,
        "damage_type" : "抓伤"
]),
([      "action": "$N双手平伸，十指微微上下抖动，奋力抓向$n的$l",
        "force" : 160,
        "attack": 39,
        "dodge" : 32,
        "parry" : 10,
        "damage": 25,
        "lvl"   : 20,
        "damage_type" : "抓伤"
]),
([      "action": "$N悄无声息的游走至$n身前，猛的一爪奋力抓向$n的$l",
        "force" : 172,
        "attack": 42,
        "dodge" : 38,
        "parry" : 19,
        "damage": 29,
        "lvl"   : 40,
        "damage_type" : "抓伤"
]),
([      "action": "$N双手平提胸前，左手护住面门，右手陡然抓向$n的$l",
        "force" : 187,
        "attack": 45,
        "dodge" : 41,
        "parry" : 21,
        "damage": 33,
        "lvl"   : 60,
        "damage_type" : "抓伤"
]),
([      "action": "$N低喝一声，双手化掌为爪，一前一后抓向$n的$l",
        "force" : 203,
        "attack": 51,
        "dodge" : 49,
        "parry" : 22,
        "damage": 36,
        "lvl"   : 80,
        "damage_type" : "抓伤"
]),
([      "action": "$N右腿斜插$n二腿之间，上手取目，下手直勾$n的喉部",
        "force" : 245,
        "attack": 56,
        "dodge" : 53,
        "parry" : 27,
        "damage": 41,
        "lvl"   : 100,
        "damage_type" : "抓伤"
]),
([      "action": "$N狂喝一声，双爪如狂风骤雨般对准$n的$l连续抓出",
        "force" : 270,
        "attack": 61,
        "dodge" : 58,
        "parry" : 38,
        "damage": 45,
        "lvl"   : 120,
        "damage_type" : "抓伤"
])
});

int valid_enable(string usage)
{
        return usage == "claw" ||  usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练锁喉功必须空手。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，无法学锁喉功。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力修为太弱，无法练锁喉功。\n");

        if ((int)me->query_skill("claw", 1) < 80)
                return notify_fail("你的基本抓法不够，无法学锁喉功。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("suohou-gong", 1))
                return notify_fail("你的基本抓法火候水平有限，无法领会更高深的锁喉功。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

/*
mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("suohou-gong", 1);

        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}
*/
mapping query_action(object me, object weapon)
{
        int lvl_temp = random((int)me->query_skill("suohou-gong", 1));
        if( lvl_temp>100 && query("neili", me)>800 )
        {
                if (lvl_temp <= 150)
                {
                        addn("neili", -50, me);
                        return ([
                                "action":"$N右手一抬，势做阴柔，无声无息袭向$n，跟着左爪突然而出，以阳刚\n之力，左右合击直取$n的喉咙。",
                                "damage_type": "内伤",
                                "dodge": -35+random(20),
                                "parry": 25+random(30),
                                "force" : 80+random(100),
                        ]);
                }
                else
                {
                        addn("neili", -80, me);
                        return ([
                                "action":"$N内力勃发，姿势凶狠，眼露凶光，招招不离$n的要害部位，似乎要将$n生吞活剥。\n"
                                 "$N双手连扬，连出阴招，不离锁喉，撩阴。$n稍有疏忽不免死得惨酷无比。",
                                "damage_type": "抓伤",
                                "dodge": -35+random(20),
                                "parry": 25+random(30),
                                "force" : 80+random(200),
                        ]);
                }
        }
        return ([
                "action"     : action_msg[random(sizeof(action_msg))],
                "damage_type": random(2)?"抓伤":"内伤",
                "dodge"      : -35+random(20),
                "parry"      : 25+random(30),
                "force"      : 80+random(100),
        ]);
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("锁喉功必须空手练习！\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够练锁喉功。\n");

        me->receive_damage("qi", 60);
        addn("neili", -69, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"suohou-gong/" + action;
}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n锁喉功："NOR"\n");
        write(@HELP

    锁喉功为丐帮的武技。

        学习要求：
                混天气功20级
                内力100
HELP
        );
        return 1;
}
