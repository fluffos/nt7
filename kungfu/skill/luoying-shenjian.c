// luoying-shenjian.c 落英神剑

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "skill_name" : "落英缤纷",
        "action" : "$N使一招"HIW"「落英缤纷」"NOR"，身形向上飘起，手中$w虚虚实实幻出万点剑花纷纷扬扬撒向$n$l",
        "lvl"    : 0
]),
([        "skill_name" : "人面桃花",
        "action" : "$N舞动$w，一式"MAG"「人面桃花」"NOR"，左手向$n面门一晃，右手$w抖出几朵剑花挟着虎虎剑气刺向$n的$l",
        "lvl"    : 10
]),
([        "skill_name" : "急风骤雨",
        "action" : "$N身形绕$n一转，手中$w望空一指，一式"BLU"「急风骤雨」"NOR"幻出满天剑影，向$n$l接连挥出数剑",
        "lvl"    : 20
]),
([        "skill_name" : "江城飞花",
        "action" : "$N身形飘然而起，在半空中身子一旋，悠然一式"RED"「江城飞花」"NOR"手中$w若有若无淡淡刺向$n的$l",
        "lvl"    : 30
]),
([        "skill_name" : "万花齐落",
        "action" : "$N纵起丈余，一式"HIW"「细云巧翻胸」"NOR"头下脚上，一招"HIR "「万花齐落」"NOR"手中$w舞成一个光球罩向$n的$l",
        "lvl"    : 40
]),
([        "skill_name" : "漫天花雨",
        "action" : "$N一声大喝使出"HIM"「漫天花雨」"NOR"，手中$w幻出漫天花瓣，迅若奔雷射向$n的$l",
        "lvl"    : 50
]),
([        "skill_name" : "落花无意",
        "action" : "$N轻叹一声，手中$w怀中一抱，一时"HIB"「落花无意」"NOR"，$w锵然跃出倏的化作几点带露的桃花，飘然飞向$n的$l",
        "lvl"    : 60
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }

int valid_learn(object me)
{
        object ob;

        if( !objectp(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("你必须先找一把剑才能学习剑法。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的内功火候不够，不能练落英神剑。\n");

        if( query("max_neili", me)<250 )
                return notify_fail("你的内力修为不够，不能练落英神剑。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("luoying-shenjian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的落英神剑。\n");

        return 1;
}
int practice_skill(object me)
{
        object ob;

        if( query("qi", me)<35 || query("neili", me)<15 )
                return notify_fail("你的内力或气不够，没办法练习落英神剑。\n");
        if( !objectp(ob=query_temp("weapon", me) )
                 || query("skill_type", ob) != "sword" )
                return notify_fail("你必须先找一把剑才能习练剑法。\n");
        me->receive_damage("qi", 35);
        addn("neili", -15, me);
        write("你按著所学练了一遍落英神剑。\n");
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
        int d_e1 = -55;
        int d_e2 = -45;
        int p_e1 = -65;
        int p_e2 = -55;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 150;
        int m_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("luoying-shenjian", 1);
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
                "damage_type" : random(2) ? "割伤" : "刺伤",
        ]);
}
int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"luoying-shenjian/" + action;
}

int help(object me)
{
        write(HIC"\n落英神剑："NOR"\n");
        write(@HELP

    落英神剑为东海桃花岛主黄药师所创。
    在桃花岛竹林内“积翠亭”两旁，悬着一副对联：“桃花影里
飞神剑，碧海潮生按玉箫”，隐然黄药师生平两大得意武功。其中
之一就是落英神剑。

        学习要求：
                碧波神功30级
                内力100
HELP
        );
        return 1;
}
