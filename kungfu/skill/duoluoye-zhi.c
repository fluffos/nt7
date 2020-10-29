// This program is a part of NT MudLIB
// duoluoye-finger.c 多罗叶指 和大金刚神掌互备 截自佛经中之“欲界诸天”。

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
int is_pbsk() { return 1; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一式"HIY"「四天王天」"NOR"，连出四指，带起空中无限气劲，一道道地插向$n$l",
        "lvl"   : 0,
        "skill_name" : "四天王天"
]),
([        "action" : "$N面带笑容使出"HIC"「仞利天」"NOR"，身形微侧，手指从袖底穿出，挟一股极利的劲力刺向$n",
        "lvl"   : 20,
        "skill_name" : "仞利天"
]),
([        "action" : "$N一式"HIB"「夜摩天」"NOR"，左掌立刃大开大阖，右手飘忽灵动，忽然一指点出，刺向$n$l！",
        "lvl"   : 40,
        "skill_name" : "夜摩天"
]),
([        "action" : "$N使出一招"CYN"「兜率天」"NOR"，左掌连劈，劲力罩住$n的身子，右手一挥，一指点向$n$l",
        "lvl"   : 60,
        "skill_name" : "兜率天"
]),
([        "action" : "$N双手抱圆，内力运行，"YEL"「化乐天」"NOR"击出，一缕指风飞袭$n，看似无力，实是无坚不摧",
        "lvl"   : 80,
        "skill_name" : "化乐天"
]),
([        "action" : "$N向$n连点数指，劲风更激起无数尖啸之声，这招"MAG"「他化自在天」"NOR"虚虚实实，防不胜防",
        "lvl"   : 100,
        "skill_name" : "他化自在天"
]),
});

string main_skill() { return "canhe-zhi"; }

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已将这种指法融入参合指，不必再分开练习了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练多罗叶指必须空手。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，无法学习多罗叶指。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力太弱，无法练多罗叶指。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("duoluoye-zhi", 1))
                return notify_fail("你的基本指法水平有限，无法领会更高深的多罗叶指。\n");

        return 1;
}

int practice_skill(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已将这种指法融入参合指，不必再分开练习了。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手练习。\n");

        if( query("qi", me)<130 )
                return notify_fail("你的体力太低了，无法练多罗叶指。\n");

        if( query("neili", me)<110 )
                return notify_fail("你的内力不够，无法练多罗叶指。\n");

        me->receive_damage("qi", 110);
        addn("neili", -100, me);
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
        int d_e1 = 40;
        int d_e2 = 60;
        int p_e1 = -20;
        int p_e2 = 0;
        int f_e1 = 150;
        int f_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("duoluoye-finger", 1);
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

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"duoluoye-finger/" + action;
}

int help(object me)
{
        write(HIC"\n多罗叶指："NOR"\n");
        write(@HELP

    多罗叶指是南少林的指法，和大金刚神掌互备，出自佛经中之“欲界诸天”。

        学习要求：
                站桩功50级
                波罗蜜手50级
                摩诃指50级
                内力修为500
HELP
        );
        return 1;
}
