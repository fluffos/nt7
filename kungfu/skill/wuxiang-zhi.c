// wuxiang-zhi.c - 少林无相指法

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
int is_pbsk() { return 1; }

mapping *action = ({
([        "action" : "$N将双手拢在衣袖之中，一招"HIW"「广大无相劫」"NOR"，暗劲自袖中悄悄涌出，刺向$n",
        "lvl"   : 0,
        "skill_name" : "广大无相劫"
]),
([        "action" : "$N微微一笑，一招"HIW"「智慧无相劫」"NOR"，衣袖连摆，指劲随机弹出，叫人琢磨不透，无法躲避",
        "lvl"   : 10,
        "skill_name" : "智慧无相劫"
]),
([        "action" : "$N垂手站立，丝毫不动，但闻$n身前哧的一声，闻声不见物，是那招"HIW"「真如无相劫」"NOR"",
        "lvl"   : 30,
        "skill_name" : "真如无相劫"
]),
([        "action" : "$N抬头往天，一指"HIW"「性海无相劫」"NOR"暗袭$n$l，本人却见丝毫不动，仿若无事发生一样",
        "lvl"   : 60,
        "skill_name" : "性海无相劫"
]),
([        "action" : "$N一招"HIW"「颖悟无相劫」"NOR"向$n点出，闻得一破空之声，却见$P微笑点头，却再无任何动静",
        "lvl"   : 100,
        "skill_name" : "颖悟无相劫"
]),
([        "action" : "但闻哧哧两声，$n脸色突变，$N却悠闲自在，并无动过手的迹象，这好象是那招"HIW"「圆觉无相劫」"NOR"",
        "lvl"   : 150,
        "skill_name" : "圆觉无相劫"
]),
});

/*
mapping *action = ({
([     "action": "$N随手前踏上一步，右指中宫直进，一式「无声无息」击向$n的$l",
       "force" : 80,
       "attack": 20,
       "parry" : 20,
       "dodge" : -5,
       "damage": 20,
       "lvl"   : 0,
       "skill_name" : "无声无息",
       "damage_type" : "刺伤"
]),
([     "action": "$N一招「无欲无望」，轻唱一声佛号，左右看似随意一弹，一屡劲风已射向$n",
       "force" : 90,
       "attack": 30,
       "parry" : 5,
       "dodge" : 20,
       "damage": 50,
       "lvl"   : 40,
       "skill_name" : "无欲无望",
       "damage_type" : "刺伤"
]),
([     "action": "$N身形飘忽不定，一式「无法无天」，右指击向$n的$l",
       "force" : 150,
       "attack": 50,
       "parry" : 35,
       "dodge" : 25,
       "damage": 80,
       "lvl"   : 80,
       "skill_name" : "无法无天",
       "damage_type" : "刺伤"
]),
([     "action": "$N脚踏七星步，突然一招「佛光普照」，左指从意想不到的角度攻向$n的各大要穴",
       "force" : 180,
       "attack": 70,
       "parry" : 35,
       "dodge" : -10,
       "damage": 100,
       "lvl"   : 120,
       "skill_name" : "佛光普照",
       "damage_type" : "刺伤"
]),
([     "action": "$N一招「佛恩济世」，背朝$n，转身一指，令$n防不胜防",
       "force" : 230,
       "attack": 70,
       "parry" : 30,
       "dodge" : 15,
       "damage": 130,
       "lvl"   : 160,
       "skill_name" : "佛恩济世",
       "damage_type" : "割伤"
]),
([     "action": "$N盘膝端坐，一招「佛法无边」，右手拇指弹出一道劲风，击向$n",
       "force" : 160,
       "attack": 60,
       "parry" : 30,
       "dodge" : 5,
       "damage": 100,
       "lvl"   : 120,
       "skill_name" : "佛法无边",
       "damage_type" : "刺伤"
]),
([     "action": "$N双目紧闭，一招「无色无相」，聚集全身内力于一指射出一道无色劲气直逼$n",
       "force" : 250,
       "attack": 100,
       "parry" : 50,
       "dodge" : 25,
       "damage": 180,
       "lvl"   : 200,
       "skill_name" : "无色无相",
       "damage_type" : "刺伤"
]),
});
*/
int valid_enable(string usage) { return usage == "finger" || usage == "parry"; }

int valid_combine(string combo) { return combo == "xuni-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练无相指必须空手。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的内功火候不够，无法学无相指。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的内力太弱，无法练无相指。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("wuxiang-zhi", 1))
                return notify_fail("你的基本指法水平有限，无法领会更高深的无相指。\n");

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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 10;
        int d_e2 = 30;
        int p_e1 = -45;
        int p_e2 = -25;
        int f_e1 = 450;
        int f_e2 = 550;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("wuxiang-zhi", 1);
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
                "damage_type" : random(2) ? "刺伤" : "瘀伤",
        ]);
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手练习！\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的内力不够练无相指。\n");

        me->receive_damage("qi", 50);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuxiang-zhi/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n无相劫指："NOR"\n");
        write(@HELP

    无相劫指是少林高级指法，不能互备，取自佛法十二字“广大，智慧，
真如，性海，颖悟，圆觉”。

        学习要求：
                一指禅50级
                内力修为2500
HELP
        );
        return 1;
}
