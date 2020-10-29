#include <ansi.h>

inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N面带微笑，一招"HIR"「烈火烧身」"NOR"，举$w对着$n连砍了八八六十四刀，刀气纵横，迅雷不可挡",
        "lvl"    : 0,
        "skill_name"  : "烈火烧身",
]),
([        "action" : "$N运起内功一招"GRN"「点木生火」"NOR"，$w上带着无比劲气，划了一个大弧，从上而下劈向$n的$l",
        "lvl"    : 20,
        "skill_name"  : "点木生火",
]),
([        "action" : "$N手臂一沉，一招"HIM"「张弓望月」"NOR"，双手持$w划出一道雪亮刀光，接着拦腰反切，砍向$n的$l",
        "lvl"    : 40,
        "skill_name"  : "张弓望月",
]),
([        "action" : "$N挥舞$w上劈下撩，左挡右开，使出一招"RED"「烈火腾云」"NOR"，卷起阵阵刀风，齐齐罩向$n",
        "lvl"    : 60,
        "skill_name"  : "烈火腾云",
]),
([        "action" : "$N一招"MAG"「火中取栗」"NOR"，左脚跃步落地，手中$w单刀往前，挟着炙热的风声劈向$n的$l",
        "lvl"    : 80,
        "skill_name"  : "火中取栗",
]),
([        "action" : "$N腾空而起，半空中一招"HIW"「玉石俱焚」"NOR"，手中$w挥出满天流光般的刀影，向$n的全身卷去",
        "lvl"    : 100,
        "skill_name"  : "玉石俱焚",
]),
});

int valid_enable(string usage) { return  (usage =="parry")|| (usage =="blade"); }

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你必须先找一把刀才能练燃木刀法。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力不足，没有办法练燃木刀法，多练些内力再来吧。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候太浅，没有办法练燃木刀法。\n");

        if ((int)me->query_skill("blade", 1) < 100)
                return notify_fail("你的基本刀法火候太浅，没有办法练燃木刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("ranmu-daofa", 1))
                return notify_fail("你的基本刀法水平还不够，无法领会更高深的燃木刀法。\n");

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
        int d_e1 = 30;
        int d_e2 = 10;
        int p_e1 = -20;
        int p_e2 = -40;
        int f_e1 = 100;
        int f_e2 = 250;
        int m_e1 = 190;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("ranmu-daofa", 1);

        if (random(me->query_skill("ranmu-daofa", 1)) > 120 &&
             me->query_skill("force") > 100 &&
             query("neili", me)>1000 &&
             query_temp("weapon", me) &&
             random(10) > 6)
        {
                addn("neili", -100, me);
                return ([
                "action": HIR "$N" HIR "忽然高宣一声佛号，身体急速"
                          "旋转，遍体通红，袈裟鼓起。刹那间手中" +
                          query("name", query_temp("weapon", me) )
                          + HIR "一道火光闪过，迸\n出一股灼热的气流，"
                          "袭向$n" HIR "！" NOR,
                "dodge" : -110,
                "attack": 340,
                "force" : 302,
                "damage": 289,
                "parry" : -70,
                "damage_type": "割伤"]);
        }

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
                "damage_type" : random(2) ? "割伤" : "擦伤",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的体力不够练燃木刀法。\n");

        if( query("neili", me)<90 )
                return notify_fail("你的内力不够练燃木刀法。\n");

        me->receive_damage("qi", 75);
        addn("neili", -85, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        if (damage < 100) return 0;
        if (random(damage) > victim->query_str()/10)
        {
                result = ([ "damage": damage ]);
                result += (["msg" : HIW "$N手中的大刀顿时化作一团火焰，激荡的炙流窜入$n体内，$n" BLINK +
                                    HIR "鲜血" NOR + HIW "狂喷而出！\n" NOR ]);
                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"ranmu-daofa/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1; }

int help(object me)
{
        write(HIC"\n燃木刀法："NOR"\n");
        write(@HELP

    燃木刀法是少林顶级刀法。
    韦陀杵、日月鞭法和燃木刀法并列为南少林三绝技。
    三绝技不能同时修习。

        学习要求：
                易筋经150级
                修罗刀150级
                内力修为1500
HELP
        );
        return 1;
}
