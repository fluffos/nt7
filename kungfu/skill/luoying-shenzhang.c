#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N双手平伸，向外掠出，一式"GRN"「春云乍展」"NOR"，指尖轻盈漂动，轻轻反点$n的$l",
        "lvl" : 10,
        "skill_name" : "春云乍展"
]),
([        "action" : "$N右手五指缓缓一收，一式"HIG"「回风拂柳」"NOR"，五指忽然遥遥拂向$n，$n只觉得五股疾风袭向自己五处大穴",
        "lvl" : 0,
        "skill_name" : "回风拂柳"
]),
([        "action" : "$N突然纵身跃入半空，一个轻巧转身，单掌劈落，一式"MAG "「江城飞花」"NOR"，拍向$n的头顶",
        "lvl" : 10,
        "skill_name" : "江城飞花"
]),
([        "action" : "$N突然跃起，双手连环，运掌如剑，势如疾风电闪，一式"HIM "「雨急风狂」"NOR"，攻向$n的全身",
        "lvl" : 10,
        "skill_name" : "雨急风狂"
]),
([        "action" : "$N左手挥起，掌心朝天，伸出右手并拢食指中指，捻个剑决，一式"CYN"「星河在天」"NOR"，直指$n的中盘",
        "lvl" : 20,
        "skill_name" : "星河在天"
]),
([        "action" : "$N突然抽身而退，接着一式"HIW"「流华纷飞」"NOR"，平身飞起，双掌向$n的后脑连拍数掌",
        "lvl" : 30,
        "skill_name" : "流华纷飞"
]),
([        "action" : "$N突然抽身跃起，左掌挟着劲风汹涌拍出，接着右掌自左掌后突地伸出，一式"HIR"「彩云追月」"NOR"抢在左掌前向$n的$l拍去",
        "lvl" : 30,
        "skill_name" : "彩云追月"
]),
([        "action" : "$N使一式"HIC"「天如穹庐」"NOR"，全身突然飞速旋转，双掌忽前忽后，猛地拍向$n的胸口",
        "lvl" : 40,
        "skill_name" : "天如穹庐"
]),
([        "action" : "$N前后一揉，一式"HIB"「朝云横度」"NOR"，化掌如剑，一股凌厉剑气袭向$n的下盘",
        "lvl" : 50,
        "skill_name" : "朝云横度"
]),
([        "action" : "$N使一式"HIW"「白虹经天」"NOR"，双掌舞出无数圈劲气，一环环向$n的$l斫去",
        "lvl" : 70,
        "skill_name" : "白虹经天"
]),
([        "action" : "$N双手食指和中指一和，一式"HIM"「紫气东来」"NOR"，一股强烈的气流涌向$n的全身",
        "lvl" : 60,
        "skill_name" : "紫气东来"
]),
([        "action" : "$N一式"HIC"「落英漫天」"NOR"，双掌在身前疾转，掌花飞舞，铺天盖地直指向$n。$n只见漫天掌花，眼花缭乱。",
        "lvl" : 99,
        "skill_name" : "落英漫天"
])
});
/*
mapping *action = ({
([      "action" : "$N右手五指缓缓一收，一式「回风拂柳」，五指忽然拂向$n五处大穴",
        "force"  : 80,
        "attack" : 14,
        "dodge"  : 7,
        "parry"  : 8,
        "damage" : 5,
        "lvl"    : 0,
        "damage_type" : "内伤",
        "skill_name"  : "回风拂柳"
]),
([      "action" : "$N陡然一个轻巧转身，单掌劈落，一式「江城飞花」，拍向$n的头顶",
        "force"  : 91,
        "attack" : 17,
        "dodge"  : 10,
        "parry"  : 13,
        "damage" : 9,
        "lvl"    : 20,
        "damage_type" : "瘀伤",
        "skill_name"  : "江城飞花"
]),
([      "action" : "$N突然跃起，双手连环，运掌如剑，一式「雨急风狂」，攻向$n的全身",
        "force"  : 108,
        "attack" : 22,
        "dodge"  : 17,
        "parry"  : 15,
        "damage" : 12,
        "lvl"    : 40,
        "damage_type" : "瘀伤",
        "skill_name"  : "雨急风狂"
]),
([      "action" : "$N突然抽身而退，一式「流华纷飞」，平身飞起，双掌向$n连拍数掌",
        "force"  : 180,
        "attack" : 33,
        "dodge"  : 13,
        "parry"  : 16,
        "damage" : 28,
        "lvl"    : 60,
        "damage_type" : "瘀伤",
        "skill_name"  : "流华纷飞"
]),
([      "action" : "$N突然抽身跃起，右掌翻滚，一式「彩云追月」抢在左掌前向$n的$l拍去",
        "force"  : 210,
        "attack" : 38,
        "dodge"  : 30,
        "parry"  : 25,
        "damage" : 33,
        "lvl"    : 80,
        "damage_type" : "瘀伤",
        "skill_name"  : "彩云追月"
]),
([      "action" : "$N使一式「白虹经天」，双掌舞出无数圈劲气，一环环向$n的$l斫去",
        "force"  : 310,
        "attack" : 72,
        "dodge"  : 41,
        "parry"  : 55,
        "damage" : 68,
        "lvl"    : 100,
        "damage_type" : "内伤",
        "skill_name"  : "白虹经天"
]),
([      "action" : "$N一式「落英漫天」，双掌在身前疾转，掌花飞舞，铺天盖地直指向$n",
        "force"  : 378,
        "attack" : 84,
        "dodge"  : 41,
        "parry"  : 65,
        "damage" : 103,
        "lvl"    : 120,
        "damage_type" : "瘀伤",
        "skill_name"  : "落英漫天"
]),
//新增三招
([      "action" : "[1;32m$N一式「柳吉祥」，双掌如柳絮般在胸前摆动，顿时一道道暗劲快速冲向$n[2;37;0m",
        "force"  : 400,
        "attack" : 200,
        "dodge"  : 200,
        "parry"  : 200,
        "damage" : 250,
        "lvl"    : 300,
        "damage_type" : "内伤",
        "skill_name"  : "[1;32m柳吉祥[2;37;0m"
]),
([      "action" : "[1;37m$N的落英神掌已修炼至大成，一招「弧月斩」，猛然凌空飞起，当头向$n斩去[2;37;0m",
        "force"  : 500,
        "attack" : 300,
        "dodge"  : 300,
        "parry"  : 300,
        "damage" : 350,
        "lvl"    : 350,
        "damage_type" : "内伤",
        "skill_name"  : "[1;37m弧月斩[2;37;0m"
]),
([      "action" : "[1;36m$N的落英神掌已入返璞归真境界，运起全身内力，一招「碧涛颂」，如海浪般的

内力向$n涌去，顿时三丈范围内沙石飞旋，眼见$n已无处可逃[2;37;0m",
        "force"  : 850,
        "attack" : 500,
        "dodge"  : 500,
        "parry"  : 500,
        "damage" : 750,
        "lvl"    : 400,
        "damage_type" : "内伤",
        "skill_name"  : "[1;36m碧涛颂[2;37;0m"
])
});
*/
int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "xuanfeng-tui";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练落英神剑掌必须空手。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的基本内功火候不够，无法学落英神剑掌。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力太弱，无法练落英神剑掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("luoying-shenzhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的落英神剑掌。\n");

        /*
        if( query("character", me) == "阴险奸诈" )
                return notify_fail("学习落英神剑掌需要博大的胸怀，没有此等胸怀是无法领悟的。\n");
        */

        if( query("str", me)<22 )
                return notify_fail("你先天臂力不足，无法修炼落英神剑掌。\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("你的基本掌法不够娴熟，无法修炼落英神剑掌。\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("你的基本掌法不够娴熟，无法修炼落英神剑掌。\n");

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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -35;
        int d_e2 = -15;
        int p_e1 = -45;
        int p_e2 = -35;
        int f_e1 = 180;
        int f_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("luoying-shenzhang", 1);
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
                "damage_type" : random(2) ? "内伤" : "瘀伤",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<300 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够练落英神剑掌。\n");

        me->receive_damage("qi", 45);
        addn("neili", -40, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"luoying-shenzhang/" + action;
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n落英神剑掌："NOR"\n");
        write(@HELP

    落英神剑掌脱胎于落英神剑，以掌代剑，威力不逊。
    可与旋风扫叶腿互备。

        学习要求：
                碧波神功15级
                内力100
HELP
        );
        return 1;
}
