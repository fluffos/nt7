// murong-jiafa 慕容剑法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N虚步提腰，上身微微前倾，一式"MAG"「洗耳恭听」"NOR"，手中$w轻轻颤动，一剑点向$n的$l",
        "lvl"   : 0,
        "skill_name" : "洗耳恭听"
]),
([        "action" : "$N向前跨上一步，左手剑诀，右手$w使出一式"GRN"「明察秋毫」"NOR"直刺$n的$l",
        "lvl"   : 20,
        "skill_name" : "明察秋毫"
]),
([        "action" : "$N身形往右一挫，左手剑诀，右手$w圈转如轮，使出一式"BLU "「甜言蜜语」"NOR"，如雪片飘落般向$n削去",
        "lvl"   : 40,
        "skill_name" : "甜言蜜语"
]),
([        "action" : "$N转身急行数步，双膝猛地下沉，右手$w匹练般回刺，劲风煞然，剑
气雄浑已极，正是一式"YEL"「望尘莫及」"NOR"",
        "lvl"   : 60,
        "skill_name" : "望尘莫及"
]),
([        "action" : "$N一招"HIB"「骑虎难下」"NOR"，飞身跃起，两腿分腿平蹬，$w自上而下划出一个大弧，平平地向$n的$l挥去",
        "lvl"   : 80,
        "skill_name" : "骑虎难下"
]),
([        "action" : "$N上身往左侧一拧，一招"HIC"「抛砖引玉」"NOR"，右手$w反手向$n的$l斜斜挥去",
        "lvl"   : 100,
        "skill_name" : "抛砖引玉"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }
int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("parry", 1) < 10)
                return notify_fail("你的基本招架火候太浅。\n");
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
        int d_e1 = 0;
        int d_e2 = 20;
        int p_e1 = -30;
        int p_e2 = -10;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 130;
        int m_e2 = 220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("murong-sword", 1);
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

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
        if( query("qi", me)<70 )
                return notify_fail("你的体力不够练慕容剑法。\n");
        if( query("neili", me)<70 )
                return notify_fail("你的内力不够练慕容剑法。\n");
        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"murong-jianfa/" + action;
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n慕容剑法："NOR"\n");
        write(@HELP

    慕容剑法为江南姑苏慕容祖传剑法。

        学习要求：
                内力100
HELP
        );
        return 1;
}
