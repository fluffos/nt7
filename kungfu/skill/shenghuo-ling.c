// This program is a part of NT MudLIB
// shenghuo-ling.c 圣火令法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N踏上一步，忽地在地上一坐，已抱住了$n小腿。十指扣住了$n小腿上的
‘中都’‘筑宾’两穴，$n只觉下半身酸麻难动，大吃一惊",
         "lvl" : 0
]),
([      "action" : "突然之间，$N身形晃动，同时欺近，手中$w往$n身上划去。脚下不知如何
移动，身形早变。右手同时抓住$n后领，一抖之下，将$n向外远远掷了出去",
        "lvl" : 10
]),
([      "action" : "$N欺身直进，左手持$w向$n天灵盖上拍落。便在这一瞬之间，$n滚身向左，
已然一拳打在$n腿上。$n一个踉跄，$N横过$w戳向$n后心",
        "lvl" : 20
]),
([      "action" : "$N忽地放手，手中那柄$w尾端向上弹起，拍的一响，正好打中$n手腕。",
        "lvl" : 30
]),
([      "action" : "$N忽然低头，一个头锤向$n撞来，$n不动声色，向旁又是一让，突觉胸口
一痛，已被$N手肘撞中",
        "lvl" : 40
]),
([      "action" : "$N手中$w急挥横扫，突然连翻三个空心筋斗。$n不知对方是何用意，心想还是避之
为妙，刚向左踏开一步，眼前白光急闪，$N的$w已到右肩",
        "lvl" : 50
]),
([      "action" : "$N忽然低头，一个头锤向$n撞来，$n不动声色，向旁又是一让，突觉胸口
一痛，已被$N手肘撞中",
        "lvl" : 60
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if (query("int", me) < 32)
                return notify_fail("你先天悟性不足，无法领会圣火令法。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的内功火候不到，无法学习圣火令法。\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("你的基本剑法火候不到，无法学习圣火令法。\n");

        if (query("max_neili", me) < 2400)
                return notify_fail("你的内功修为不足，无法学习圣火令法。\n");

        if (me->query_str() < 35)
                return notify_fail("你现在膂力太差，无法学习圣火令法。\n");

        if (me->query_int() < 40)
                return notify_fail("你现在无法领悟圣火令法的要诣。\n");

        if (me->query_dex() < 35)
                return notify_fail("你现在身法太差，无法学习圣火令法。\n");

        if (me->query_skill("force", 1) < me->query_skill("shenghuo-ling", 1))
                return notify_fail("你的内功修为不足，无法领会更高深的圣火令法。\n");

        if (me->query_skill("shenghuo-ling", 1) > 200)
        {
                 if (me->query_skill("shenghuo-ling", 1) >
                     me->query_skill("shenghuo-shengong", 1))
                            return notify_fail("你的圣火神功水平有限，无法领会"
                                               "更高深的圣火令法。\n");
        }

        if (me->query_skill("sword", 1) < me->query_skill("shenghuo-ling", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的圣火令法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("shenghuo-ling", 1) < 180)
                return notify_fail("你还没有掌握圣火令法中所有的奥妙，无法"
                                   "通过锻炼获得提升。\n");

        if ((int)query("qi", me) < 80)
                return notify_fail("你的体力不够练圣火令法。\n");

        if ((int)query("neili", me) < 80)
                return notify_fail("你的内力不够练圣火令法。\n");

        me->receive_damage("qi", 50);
        addn("neili", -70, me);

        return 1;
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 20;
        int d_e2 = 40;
        int p_e1 = -10;
        int p_e2 = 10;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 70;
        int m_e2 = 160;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("shenghuo-ling", 1);
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
                "damage_type" : random(2) ? "劈伤" : "刺伤",
        ]);
}

int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me)
{
        if( me->query_skill("qiankun-danuoyi", 1) < 100) return 1.0;
        if( me->query_skill("qiankun-danuoyi", 1) > 250) return 2.0;
        return (me->query_skill("qiankun-danuoyi", 1)-100)/150+1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (query_temp("shenghuo-ling/max_hit", me))
        {
                victim->receive_wound("qi", damage_bonus);
                return HIR "只听“噗嗤”一声，一股鲜血至$n" HIR "胸前射出！"
                       "\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"shenghuo-ling/" + action;
}

int help(object me)
{
        write(HIR"\n圣火令法："NOR"\n");
        write(@HELP

    圣火令法是明教圣物圣火令上的武功，以其招式怪异无比而往
打之措手不及，加上圣火令之特殊性，更是厉害无比。

        学习要求：
                九阳神功20级
                内力50
                太监无法修习50级以上的圣火令法
HELP
        );
        return 1;
}