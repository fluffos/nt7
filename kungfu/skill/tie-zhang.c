#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
int is_pbsk() { return 1; }

mapping *action = ({
([        "action" : "$N右掌一拂而起，一招"CYN"「推窗望月」"NOR"，自侧面连消带打，登时将$n的力道带斜。",
        "lvl"    : 0,
        "skill_name" : "推窗望月"
]),
([        "action" : "$N使一招"YEL"「分水擒龙」"NOR"，左掌陡然沿着伸长的右臂，飞快的一削而出，斩向$n的$l",
        "lvl"    : 10,
        "skill_name" : "分水擒龙"
]),
([        "action" : "$N突然使一式"HIW"「白云幻舞」"NOR"，双臂如旋风一般一阵狂舞，刮起一阵旋转的气浪。 ",
        "lvl"    : 20,
        "skill_name" : "白云幻舞"
]),
([        "action" : "$N一招"HIY"「掌中乾坤」"NOR"，猛地侧过身来，右臂自左肋下疾翻而出，拇，中两指扣圈猛弹$n的$l",
        "lvl"    : 30,
        "skill_name" : "掌中乾坤"
]),
([        "action" : "$N一招"RED"「落日赶月」"NOR"，伸掌一拍一收，一拍无丝毫力道，一收之间，一股阴柔无比的力道才陡然发出。",
        "lvl"    : 40,
        "skill_name" : "落日赶月"
]),
([        "action" : "$N身行暴起，一式"BLU"「蛰雷为动」"NOR"，双掌横横切出，掌缘才递出，呜呜呼啸之声狂作。",
        "lvl"    : 50,
        "skill_name" : "蛰雷为动"
]),
([        "action" : "$N一招"MAG"「天罗地网」"NOR"，左掌大圈而出，右掌小圈而出，两股奇异的力道一会之下，击向$n的$l",
        "lvl"    : 60,
        "skill_name" : "天罗地网"
]),
([        "action" : "$N一招"HIG"「五指幻山」"NOR"，猛一吐气，单掌有如推门，另一掌却是迅疾无比的一推即收。",
        "lvl"    : 80,
        "skill_name" : "五指幻山"
]),
([        "action" : "$N突然大吼一声，一招"HIR"「猛虎下山」"NOR"身行疾飞而起，猛向$n直扑而下，空气中暴出“呜”的一声刺耳尖啸。",
        "lvl"    : 100,
        "skill_name" : "猛虎下山"
]),
});

/*
mapping *action = ({
([      "action": "$N右掌一拂而起，施出「推窗望月」自侧面连消带打，登时将$n力道带斜",
        "force"  : 187,
        "attack" : 45,
        "dodge"  : 33,
        "parry"  : 32,
        "damage" : 38,
        "lvl"    : 0,
        "skill_name" : "推窗望月",
        "damage_type": "瘀伤"
]),
([      "action": "$N施出「分水擒龙」，左掌陡然沿着伸长的右臂一削而出，斩向$n的$l",
        "force"  : 212,
        "attack" : 53,
        "dodge"  : 34,
        "parry"  : 45,
        "damage" : 43,
        "lvl"    : 20,
        "skill_name" : "推窗望月",
        "damage_type": "瘀伤"
]),
([      "action": "$N一招「白云幻舞」，双臂如旋风一般一阵狂舞，刮起一阵旋转的气浪",
        "force"  : 224,
        "attack" : 67,
        "dodge"  : 45,
        "parry"  : 53,
        "damage" : 51,
        "lvl"    : 40,
        "skill_name" : "推窗望月",
        "damage_type": "瘀伤"
]),
([      "action": "$N陡然一招「掌内乾坤」，侧过身来，右臂自左肋下翻出，直拍向$n而去",
        "force"  : 251,
        "attack" : 91,
        "dodge"  : 61,
        "parry"  : 63,
        "damage" : 68,
        "lvl"    : 80,
        "skill_name" : "掌内乾坤",
        "damage_type": "瘀伤"
]),
([      "action": "$N一招「落日赶月」，伸掌一拍一收，顿时一股阴柔无比的力道向$n迸去",
        "force"  : 297,
        "attack" : 93,
        "dodge"  : 81,
        "parry"  : 87,
        "damage" : 76,
        "lvl"    : 120,
        "skill_name" : "落日赶月",
        "damage_type": "瘀伤"
]),
([      "action": "$N身行暴起，一式「蛰雷为动」，双掌横横向$n切出，呜呜呼啸之声狂作",
        "force"  : 310,
        "attack" : 91,
        "dodge"  : 67,
        "parry"  : 71,
        "damage" : 73,
        "lvl"    : 160,
        "skill_name" : "蛰雷为动",
        "damage_type": "瘀伤"
]),
([      "action": "$N一招「天罗地网」，左掌大圈而出，右掌小圈而发，两股力道同时击向$n",
        "force"  : 324,
        "attack" : 102,
        "dodge"  : 71,
        "parry"  : 68,
        "damage" : 85,
        "lvl"    : 200,
        "skill_name" : "天罗地网",
        "damage_type": "瘀伤"
]),
([      "action": "$N施一招「五指幻山」，单掌有如推门，另一掌却是迅疾无比的一推即收",
        "force"  : 330,
        "attack" : 112,
        "dodge"  : 55,
        "parry"  : 73,
        "damage" : 92,
        "lvl"    : 220,
        "skill_name" : "五指幻山",
        "damage_type": "瘀伤"
]),
([      "action": "$N突然大吼一声，一招「铁掌神威」，身行疾飞而起，再猛向$n直扑而下",
        "force"  : 321,
        "attack" : 123,
        "dodge"  : 73,
        "parry"  : 72,
        "damage" : 95,
        "lvl"    : 240,
        "skill_name" : "铁掌神威",
        "damage_type": "瘀伤"
]),
});
*/

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练铁掌掌法必须空手。\n");

        if( query("str", me)<32 )
                return notify_fail("你的先天臂力孱弱，难以修炼铁掌掌法。\n");

        if( query("con", me)<32 )
                return notify_fail("你的先天根骨孱弱，难以修炼铁掌掌法。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力修为太弱，难以修炼铁掌掌法。\n");

        if ((int)me->query_skill("force") < 230)
                return notify_fail("你的内功火候不足，难以修炼铁掌掌法。\n");

        if ((int)me->query_skill("strike", 1) < 150)
                return notify_fail("你的基本掌法火候不够，难以修炼铁掌掌法。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("tie-zhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的铁掌掌法。\n");

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
        int d_e1 = -55;
        int d_e2 = -30;
        int p_e1 = -60;
        int p_e2 = -50;
        int f_e1 = 300;
        int f_e2 = 450;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("tie-zhang", 1);
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
        int cost;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练铁掌掌法必须空手。\n");

        if( query("qi", me)<150 )
                return notify_fail("你的体力太低了。\n");

        cost = me->query_skill("tie-zhang", 1) / 5 + 80;

        if( query("neili", me)<cost )
                return notify_fail("你的内力不够练铁掌掌法。\n");

        me->receive_damage("qi", 120);
        addn("neili", -cost, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("tie-zhang", 1);

        if (damage_bonus < 150 || lvl < 150)
                return 0;

        if (damage_bonus / 6 > victim->query_con()/10
            /*&& random(2) == 1*/)
        {
                victim->receive_wound("qi", (damage_bonus - 90) / 2, me);

                return random(2) ? HIR "只听$n" HIR "前胸「咔嚓」一声脆响，竟像是"
                                   "肋骨断折的声音。\n" NOR:

                                   HIR "$n" HIR "一声惨叫，胸前「咔嚓咔嚓」几声脆"
                                   "响，口中鲜血狂喷。\n" NOR;
        }
}

/*
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lev,damage, i;
        string msg;
        object weap;
        object piece;
        weap=query_temp("weapon", victim);
        lev=query("tiezhang-zhangfa", me);

        if( (query("neili", me)>1000) &&
                (query_temp("weapon", victim)) &&
                (query_temp("tzzf", me)) &&
                (random(me->query_str()) > victim->query_str()/2) )
        {
                if( random(query("rigidity", weap))<3 )
                {
                        message_combatd(HIW"$N运掌如刀，连击三十六下，只听见「啪」地一声，$n手中的" + weap->name() + "已经断为两截！\n" NOR, me, victim );
                        seteuid(getuid());
                        piece = new("/clone/misc/piece");
                        piece->set_name("断掉的"+query("name", weap),({query("id", weap),"piece"}));
                        piece->move(environment(me));
                        destruct(weap);
                }
                else
                {
                        message_combatd(HIW"$N运掌如刀，连击三十六下，只听见「当」地一声，$n手中的" + weap->name() + "被刀气震落到地上！\n" NOR, me,victim );
                        weap->move(environment(me));
                }
                victim->reset_action();
                addn("neili", -100, me);
                return 1;
        }
}
*/
string perform_action_file(string action)
{
        return __DIR__"tie-zhang/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n铁掌掌法："NOR"\n");
        write(@HELP

    铁掌掌法是铁掌帮镇帮掌法。
    铁掌掌力浑厚恶毒，与降龙十八掌、黯然销魂掌并称天下。


        学习要求：
                归元吐纳法100级
                内力修为1000
HELP
        );
        return 1;
}
