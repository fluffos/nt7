#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
int is_pbsk() { return 1; }

string *dodge_msg = ({
        "$n身形微微一晃，双足连环踢出，将$N硬生生迫退。\n",
        "$n错步上前，单足忽的一抬，将$N的攻势全部挡回，只能自保。\n",
        "$n双足轻轻点地，猛的拔地而起，躲开了$N的招式。\n",
});

mapping *action = ({
([        "action" : "$N双手虚晃，左脚猛地飞起，一式"HIC"「风起云涌」"NOR"，脚尖晃动，踢向$n的屁股",
        "lvl" : 0,
        "skill_name" : "风起云涌"
]),
([        "action" : "$N左脚顿地，别转身来抽身欲走，只一刹那间一回身，右脚一式"HIB"「空谷足音」"NOR"，猛踹$n的$l",
        "lvl" : 0,
        "skill_name" : "空谷足音"
]),
([        "action" : "$N左手一挣，反手扭搭住$n的右手，右脚同时踹出，既猛且准，一式"GRN"「碧渊腾蛟」"NOR"，踢中的$n的胸口",
        "lvl" : 10,
        "skill_name" : "碧渊腾蛟"
]),
([        "action" : "$N突然跃起，双足连环圈转，一式"HIY"「秋风落叶」"NOR"，足带风尘，攻向$n的全身",
        "lvl" : 10,
        "skill_name" : "秋风落叶"
]),
([        "action" : "$N两手护胸，双脚交叉踢起，一式"HIW"「风扫残云」"NOR"，脚脚不离$n的面门左右",
        "lvl" : 20,
        "skill_name" : "风扫残云"
]),
([        "action" : "$N突然侧身，却步后退，一个前空翻，右脚自上而下一式"HIM "「流星坠地」"NOR"，照$n的面门直劈下来",
        "lvl" : 30,
        "skill_name" : "流星坠地"
]),
([        "action" : "$N使一式"HIW"「朔风吹雪」"NOR"，全身突然飞速旋转，双足忽前忽后，迅猛无极踹向$n的胸口",
        "lvl" : 40,
        "skill_name" : "朔风吹雪"
]),
([        "action" : "$N抽身跃起，开声吐气，大喝一声：嗨！一式"MAG"「雷动九天」"NOR"，双脚如旋风般踢向$n的$l",
        "lvl" : 30,
        "skill_name" : "雷动九天"
]),
});

int valid_enable(string usage)
{
        return usage == "unarmed" ||  usage == "parry" ||  usage == "dodge";
}

int valid_combine(string combo)
{
        return combo == "luoying-shenzhang";
}

int valid_learn(object me)
{
            if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("学习旋风扫叶腿必须空手。\n");

            if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，无法学旋风扫叶腿。\n");

            if( query("max_neili", me)<800 )
                return notify_fail("你的内力太弱，无法练旋风扫叶腿。\n");

            if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("xuanfeng-tui", 1))
                return notify_fail("你的基本拳脚水平有限，无法领会更高深的旋风扫叶腿。\n");

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("xuanfeng-tui", 1))
                return notify_fail("你的基本轻功水平有限，无法领会更高深的旋风扫叶腿。\n");

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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 5;
        int d_e2 = 25;
        int p_e1 = -45;
        int p_e2 = 30;
        int f_e1 = 350;
        int f_e2 = 450;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("xuanfeng-tui", 1);
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

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
            if( query("qi", me)<60 )
                       return notify_fail("你的体力太低了。\n");

            if( query("neili", me)<60 )
                       return notify_fail("你的内力不够练旋风扫叶腿。\n");

            me->receive_damage("qi", 45);
            addn("neili", -51, me);
            return 1;
}

string perform_action_file(string action)
{
            return __DIR__"xuanfeng-tui/" + action;
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n旋风扫叶腿："NOR"\n");
        write(@HELP

    旋风扫叶腿是东海桃花岛主黄药师所创武功。
    可与落英神剑掌互备。

        学习要求：
                碧波神功15级
                内力100
HELP
        );
        return 1;
}
