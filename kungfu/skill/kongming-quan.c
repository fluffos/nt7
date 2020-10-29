// kongming.c 空明拳

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action": "$N使一招"HIW"「空屋住人」"NOR"，双手轻飘飘地箍向$n$l",
        "lvl":0,
        "skill_name": "空屋住人"
]),
([        "action": "$N左掌一平,右掌一伸,一招"HIW"「空碗盛饭」"NOR"直拍$n的$l",
        "lvl":10,
        "skill_name": "空碗盛饭"
]),
([        "action": "$N身形绕$n一转，双手上撩,一招"HIW"「空钵装水」"NOR"击向$n$l",
        "lvl":20,
        "skill_name": "空钵装水"
]),
([        "action": "$N左掌一按,右掌一挥,一招"HIW"「虚怀若谷」"NOR"拍向$n的$l",
        "lvl":30,
        "skill_name": "虚怀若谷"
]),
([        "action": "$N使一招"HIW"「空山鸟语」"NOR"，$n的$l已围在$N的重重掌影之下",
        "lvl":40,
        "skill_name": "空山鸟语"
]),
([        "action": "$N神色一敛，使出"HIW"「我心空明」"NOR"，围绕$n的$l接连出掌",
        "lvl":50,
        "skill_name": "我心空明"
]),
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry" || usage=="cuff"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练空明拳必须空手。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力太弱，无法练空明拳。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，无法练空明拳。\n");

        if ((int)me->query_skill("unarmed", 1) < 120)
                return notify_fail("你的基本拳脚火候不够，无法练空明拳。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("kongming-quan", 1))
                return notify_fail("你的基本拳脚水平有限，无法领会更高深的空明拳。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必须空手才能练习。\n");
        if( query("qi", me)<70 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<70 )
                return notify_fail("你的内力不够了！休息一下再练吧。\n");
        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -5;
        int d_e2 = -20;
        int p_e1 = -50;
        int p_e2 = -60;
        int f_e1 = 400;
        int f_e2 = 500;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("kongming-quan", 1);
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

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;

        if ((int)me->query_skill("kongming-quan", 1) < 100
           || ! living(me)
            || query_temp("weapon", me )
            || query_temp("weapon", ob) )
                return;

        ap = ob->query_skill("force") + ob->query_skill("count", 1);
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("kongming-quan", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "双臂一格，$N" + HIG
                                            "登时觉得自己的力道全然落空。\n"
                                            NOR]);
                        break;
                case 1:
                        result += (["msg" : HIG "$n" HIG "随意格挡，让$N" HIG
                                            "只觉得自己全然捕捉不到$n" HIG "的"
                                            "力道。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "慢慢出拳左挡右格，让"
                                            "$N" HIG "只觉得力道无处可使，说不"
                                            "出的难受。\n" NOR]);
                        break;
                }
                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("kongming-quan", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("kongming-quan", 1)) < 100 ||
            !living(me) || !query_temp("weapon", me) )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("kongming-quan", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "运起空明拳的“空”字决，$N" HIC "的攻击忽然落空。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "运起空明拳的“柔”字决，身形如蛇般缠着$N。\n"
                                    HIC "$N" HIC "根本无计可施，只得收回攻势。\n" NOR]);
                        break;
                }
                return result;
        }
}
*/

string perform_action_file(string action)
{
        return __DIR__"kongming-quan/" + action;
}

int help(object me)
{
        write(HIC"\n空明拳："NOR"\n");
        write(@HELP

    空明拳是老顽童周伯通在桃花岛囚洞中悟出来的武功。
    老子《道德经》里有句话道：“埏埴以为器，当其无，有器之
用。凿户牖以为室，当其无，有室之用。”就是说，碗只因为中间
是空的，才有盛饭的功用，倘若它是实心的一块瓷土，还能装甚么
饭？建造房屋，开设门窗，只因为有了四壁中间的空隙，房子才能
住人。倘若房屋是实心的，倘若门窗不是有空，砖头木材四四方方
的砌上这么一大堆，那就一点用处也没有了。全真派最上乘的武功，
要旨就在“空、柔”二字，那就是所谓“大成若缺，其用不弊。大
盈若冲，其用不穷”。空明拳乃是天下至柔的武功，能增强招架。

        学习要求：
                内力100
HELP
        );
        return 1;
}
