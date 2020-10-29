// This program is a part of NT MudLIB
// sun-finger.c

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *xue_name = ({
"劳宫穴", "膻中穴", "曲池穴", "关元穴", "曲骨穴", "中极穴", "承浆穴", "天突穴", "百会穴",
"幽门穴", "章门穴", "大横穴", "紫宫穴", "冷渊穴", "天井穴", "极泉穴", "清灵穴", "至阳穴", });

mapping *action = ({
([      "action" : "$N一式"GRN"「阳关三叠」"NOR"，真气自指间喷薄而出，连出三指，快如电闪，点向$n的$l",
        "lvl" : 0,
        "skill_name" : "阳关三叠"
]),
([      "action" : "$N身形一转，一步跨到$n身后。$n急忙转身，$N又如闪电般跃回，
一式"YEL"「鲁阳返日」"NOR"，右手食指疾出，指向$n的$l",
        "lvl" : 20,
        "skill_name" : "鲁阳返日"
]),
([      "action" : "$N向左踏出一步，左手轻扬，右手食指挟着雄浑内力疾点$n的$l，
招式光明坦荡，正是一式"HIW"「阳春白雪」"NOR"",
        "lvl" : 40,
        "skill_name" : "阳春白雪"
]),
([      "action" : "$N身影飘起，一式"MAG"「阳钩挥天」"NOR"，自上而下，左脚弯曲如钩，踹向$n的右肩，$n侧身相避，$N右手趁势点向$n的$l",
        "lvl" : 60,
        "skill_name" : "阳钩挥天"
]),
([      "action" : "只见$N脸上忽地一红，左手一收，一式"RED"「烈日骄阳」"NOR"，右手食指斜指，向$n的$l点去",
        "lvl" : 70,
        "skill_name" : "烈日骄阳"
]),
([      "action" : "$N左掌斜削，突然间变掌为指，嗤的一声响，一式"HIM"「丹凤朝阳」"NOR"，使出一阳指力，疾点$n的$l",
        "lvl" : 90,
        "skill_name" : "丹凤朝阳"
]),
([      "action" : "$N反身一跃，闪身到$n背后，左膝一屈，右手食指回身一式"BLU"「阴阳交错」"NOR"，射向$n的后脑",
        "lvl" : 100,
        "skill_name" : "阴阳交错"
]),
([      "action" : "$N一声大吼, 一式"HIY"「三阳开泰」"NOR"，用尽全力向$n的$l点去",
        "lvl" : 130,
        "skill_name" : "三阳开泰"
]),
});
mapping *action_staff = ({
([      "action" : "$N嘴角轻笑，提$w平胸，看准时机一杖挥出，激起呼呼风声，迅猛无比地直插$n$l",
        "force" : 100,
        "dodge" : 15,
        "damage" : 50,
        "lvl" : 0,
        "damage_type" : "刺伤",
]),
([      "action" : "$N左手捏个杖诀，右腕传动，将一阳指神功化于$w之上，出杖凝重，平平正正地打向$n",
        "force" : 150,
        "dodge" : -10,
        "damage" : 70,
        "lvl" : 20,
        "damage_type" : "内伤",
]),
([      "action" : "只见$N屏息凝神，脚步沉着，杖走刀势，一式横劈，砍向$n$l，招式威猛正大",
        "force" : 200,
        "dodge" : 0,
        "damage" : 90,
        "lvl" : 40,
        "damage_type" : "割伤",
]),
([      "action" : "$N脚下步法微变，身随杖走，端凝自重，极飘逸的一杖向$n击出，轻灵中却也不失王者气象",
        "force" : 250,
        "dodge" : 10,
        "damage" : 120,
        "lvl" : 60,
        "damage_type" : "刺伤",
]),
([      "action" : "$N平推一杖，手中的$w看似渐渐沉重，使动时略比先前滞涩，但实是举轻若重，威猛之极",
        "force" : 300,
        "dodge" : -15,
        "damage" : 140,
        "lvl" : 80,
        "damage_type" : "刺伤",
]),
});
int valid_enable(string usage)
{
        //return usage == "finger" || usage == "parry" || usage == "staff";
        return usage == "finger" || usage == "parry";
}

int valid_learn(object me)
{
/*
        if( query("gender", me) != "男性" )
                return notify_fail("一阳指乃是纯阳玄功，你如何可以修习？\n");

        if( query("str", me)<34 )
                return notify_fail("你的先天膂力孱弱，无法领会一阳指。\n");

        if( query("dex", me)<30 )
                return notify_fail("你的先天身法孱弱，无法修炼一阳指。\n");
*/

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练一阳指必须空手。\n");

        if ((int)me->query_skill("force") < 240)
                return notify_fail("你的内功火候不够，无法学一阳指。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力太弱，无法练一阳指。\n");

        if ((int)me->query_skill("finger", 1) < 150)
                return notify_fail("你的基本指法火候不够，无法学一阳指。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("sun-finger", 1))
                return notify_fail("你的基本指法水平有限，无法领会更高深的一阳指。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的内力不够练一阳指!\n");

        me->receive_damage("qi", 60);
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
        int d_e1 = 25;
        int d_e2 = 45;
        int p_e1 = -35;
        int p_e2 = -15;
        int f_e1 = 390;
        int f_e2 = 490;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("sun-finger", 1);
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
                "damage_type" : random(2) ? "刺伤" : "瘀伤",
        ]);
}
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me)
{
  if(me->query_skill("kurong-changong") > 10) return 1.0;
  else return 0.6;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name, weapon;
        name = xue_name[random(sizeof(xue_name))];

        if (victim->is_busy())
                return 0;

        if (damage_bonus < 150)
                return 0;

        if( !objectp(weapon=query_temp("weapon", me)) )
        {
                if( (query("neili", me)>300 )
                   && me->query_skill("sun-finger", 1) > 100
                   && ! victim->is_busy())
                {
                        victim->start_busy(3);
                        addn("neili", -50, me);
                        victim->receive_wound("qi", (damage_bonus - 100) / 3, me);

                        if( query("neili", victim) <= (damage_bonus/4+50) )
                                set("neili", 0, victim);
                        else
                                addn("neili", -damage_bonus/4, victim);

                                return HIR "只听“嗤”的一声，$n" HIR "被$N" HIR "凌空一指点中" NOR +
                                       HIY + name + NOR + HIR "，真气不由得一滞。\n" NOR;
                }
        } else
        {
                if( (query("neili", me)>300 )
                   && me->query_skill("sun-finger", 1) > 100
                   && ! victim->is_busy())
                {
                        victim->start_busy(2);
                        addn("neili", -50, me);
                        victim->receive_wound("qi", (damage_bonus - 120) / 3, me);

                        return HIR "只听“嗤”的一声，$n" HIR "被$N" HIR "杖端发出的气劲刺中" NOR +
                               HIY + name + NOR +HIR "，真气不由得一滞。\n" NOR;
                }
        }

}

string perform_action_file(string action)
{
        return __DIR__"sun-finger/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("yiyang-zhi", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int help(object me)
{
        write(HIC"\n一阳指："NOR"\n");
        write(@HELP

    原为大理段氏独门招牌武功，当年一灯大师段智兴挟此技参与
华山论剑，获得南帝称号。后一灯大师用一阳指和重阳真人交换先
天气功，此技亦流入全真派中。
    可与全真教昊天掌互备。

        学习要求：
                男性
                枯荣禅功或先天气功80级
                内力700
HELP
        );
        return 1;
}
