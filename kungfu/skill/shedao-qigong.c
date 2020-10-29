// shedao-qigong  蛇岛奇功
#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

/*
mapping *action = ({
([        "action" : "$N一立一个翻身，一式「乌龙盘树」，杖尾霍地横卷过来，扫击$n的$l",
        "lvl"    : 0,
        "skill_name" : "乌龙盘树"
]),
([        "action" : "$N大喝一声，手中$w化成一片银光，一招「夜战八方」，向$n的$l猛扫过去",
        "lvl"    : 10,
        "skill_name" : "夜战八方"
]),
([        "action" : "$N蓦然一声长啸，一招「流星赶月」，手中$w幻成三道白光，分袭$n胸腹要穴",
        "lvl"    : 15,
        "skill_name" : "流星赶月"
]),
([        "action" : "$N身形陡然飞起三丈多，一式「千斤压顶」，手中$w带着呼啸破空声从天而降",
        "lvl"    : 20,
        "skill_name" : "千斤压顶"
]),
([      "action" : "$N趁着$n脚步未稳，撵杖向前进招，骤然一指，杖尾起处，「毒蛇寻穴」，直取白$n丹田下“血海穴”",
        "lvl"    : 25,
        "skill_name" : "毒蛇寻穴"
]),
([      "action" : "$N杖头一转，迅即一招「横扫千军」，刚猛迅捷，如雷霆疾发向$n下三路猛扫过去",
        "lvl"    : 30,
        "skill_name" : "横扫千军"
]),
([        "action" : "陡然间，$N手中杖光华大盛，$w宛似「蛟龙出海」，登时把$n圈在当中",
        "lvl"    : 35,
        "skill_name" : "蛟龙出海"
]),
([        "action" : "$N手中$w盘旋，左右飞舞宛如银龙入海，十荡十决，一式「横云断峰」向$n的$l横扫过去",
        "lvl"    : 40,
        "skill_name" : "横云断峰",
]),
([      "action" : "$N高高跃起，挥舞着手中的$w一招「一柱擎天」犹如一条黑蟒般向$n当头直落而下",
        "lvl"    : 50,
        "skill_name" : "一柱擎天",
]),
([        "action" : "$N一声暴喝「蛟龙横空」！将$w由下往上一撩，双手握住$w尾，转身猛得横扫打向$n的$l",
        "lvl"    : 60,
        "skill_name" : "蛟龙横空",
]),
([      "action" : "$N忽然招数一变，使出「灵蛇出洞」，杖法显得灵巧之极，手中$w化作条条蛇影缠向$n",
        "lvl"    : 70,
        "skill_name" : "灵蛇出洞"
]),
([      "action" : "$N以杖代剑，$w中宫直进，夹着一阵狂风刺出，逼向$n的$l，正是招「长蛟化龙」",
        "lvl"    : 80,
        "skill_name" : "长蛟化龙"
]),
([        "action" : "$N一式「一杖定海」，当头一$w击将下来，杖头未至，一股风已将$n逼得难以喘气",
        "lvl"    : 90,
        "skill_name" : "一杖定海"
]),
([        "action" : "$N变招「群蛇狂舞」，$w扫出一道道灰影从四面八方围向$n，要将$n淹没吞食",
        "lvl"    : 100,
        "skill_name" : "群蛇狂舞"
]),
});
*/

mapping *action = ({
([        "action" : "$N使一招「仙鹤梳翎」手中$w一提，插向$n的$l",
        "damage" : 25,
        "dodge": -30,
        "parry": -40,
        "force": 90,
        "damage_type" : "挫伤",
        "skill_name" : "仙鹤梳翎"
]),
([        "action": "$N使出「灵蛇出洞」，身形微弓，手中$w倏的向$n的$l戳去",
        "damage" : 30,
        "dodge": -20,
        "parry": -10,
        "force": 140,
        "lvl"  : 30,
        "damage_type": "刺伤",
        "skill_name" : "灵蛇出洞"
]),
([        "action": "$N身子微曲，左足反踢，乘势转身，使一招「贵妃回眸」，右手$w已戳向$n$l",
        "damage" : 40,
        "dodge": -30,
        "parry": -20,
        "force": 190,
        "lvl"  : 70,
        "damage_type": "刺伤",
        "skill_name" : "贵妃回眸"
]),
([        "action" : "$N使一式「飞燕回翔」，背对着$n，右足一勾，顺势在$w上一点，$w陡然向自己咽喉疾射，接着$N身子往下一缩，$w掠过其咽喉，急奔$n急射而来",
        "damage" : 50,
        "force" : 230,
        "dodge" : -45,
        "parry" : -40,
        "lvl" : 40,
        "lvl"  : 100,
        "damage_type" : "刺伤",
        "skill_name" : "飞燕回翔"
]),
([        "action": "$N忽的在地上一个筋斗，使一招「小怜横陈」，从$n胯下钻过，手中$w直击$n",
        "damage" : 55,
        "dodge": -40,
        "parry": -30,
        "force": 270,
        "lvl"  : 120,
        "damage_type": "刺伤",
        "skill_name" : "小怜横陈"
]),
([        "action": "$N大吼一声，使一招「子胥举鼎」，反手擒拿$n极泉要穴，欲将$n摔倒在地",
        "dodge": -45,
        "parry": -50,
        "damage" : 60,
        "force": 330,
        "lvl"  : 140,
        "damage_type": "内伤",
        "skill_name" : "子胥举鼎"
]),
([        "action": "$N双腿一缩，似欲跪拜，一招「鲁达拨柳」左手抓向$n右脚足踝，右手$w直击$n小腹",
        "dodge": -50,
        "damage" : 65,
        "parry": -50,
        "force": 370,
        "lvl"  : 160,
        "damage_type": "内伤",
        "skill_name" : "鲁达拨柳"
]),
([        "action": "$N突然一个倒翻筋斗，一招「狄青降龙」，双腿一分，跨在肩头，双掌直击$n",
        "dodge": -70,
        "damage" : 75,
        "parry": -30,
        "force": 400,
        "lvl"  : 180,
        "damage_type": "内伤",
        "skill_name" : "狄青降龙"
]),
});

int valid_enable(string usage)
{
        return usage == "unarmed" ||
               usage == "sword"||
               usage == "staff"||
               usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，无法学蛇岛奇功.\n");

        if ((int)me->query_skill("shenlong-bashi", 1) < 100)
                return notify_fail("你的神龙八式火候不够，无法学蛇岛奇功。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力太弱，无法学蛇岛奇功。\n");

        /*
        if ((int)me->query_skill("shenlong-bashi", 1) < (int)me->query_skill("shedao-qigong", 1))
                return notify_fail("你的神龙八式水平有限，无法继续学蛇岛奇功。\n");
        */

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
        int d_e1 = -30;
        int d_e2 = -60;
        int p_e1 = 0;
        int p_e2 = -30;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 220;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("shedao-qigong", 1);
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
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : "挫伤",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的内力不够练蛇岛奇功。\n");

        me->receive_damage("qi", 55);
        addn("neili", -67, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shedao-qigong/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }