// tanzhi.c 弹指神通

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
string *xue_name = ({
        "劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
        "幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
});

string *action_finger = ({
        "$N中指微屈，突然弹出，一式「指点江山」，一缕劲风直袭$n的$l",
        "$N左掌在身前一划，右手突然穿出，中指微弹，「如来神指」！直袭$n的$l",
        "$N右臂挥动，中指连弹，在身前划了一道弧线，正是「一衣带水」，划向$n的前胸",
        "$N跃起在半空，双手急挥，中指连弹，「弹指惊雷」铺天盖地般向$n涌去",
});

string *action_throwing = ({
        "$N中指微屈，突然弹出，一式「指点江山」，$w破空之声甚厉，直袭$n的$l",
        "$N左掌在身前一划，右手突然穿出，中指微弹，「如来神指」！$w呼啸着直袭$n的$l",
        "$N右臂挥动，中指连弹，数个$w在身前划了一道弧线，正是「一衣带水」，划向$n的前胸",
        "$N跃起在半空，双手急挥，中指连弹，「弹指惊雷」弹出铺天盖地的$w，向$n涌去",
});
mapping *action = ({
([      "action" : "$N右指划了个半圈，一式"CYN"「划天裂地」"NOR"自上而下划向$n的全身",
        "lvl" : 0,
        "skill_name" : "划天裂地"
]),
([      "action" : "$N左掌护胸，一招"BLU"「我心悠悠」"NOR"，右指欲举无力指向$n的额头",
        "lvl" : 10,
        "skill_name" : "我心悠悠"
]),
([      "action" : "$N双手齐出，一式"YEL"「千夫所指」"NOR"，疾指向$n的$l",
        "lvl" : 20,
        "skill_name" : "千夫所指"
]),
([      "action" : "$N仰天一叹，一招"RED"「弹指人生」"NOR"，双手幻出重重指影，点向$n的$l",
        "lvl" : 30,
        "skill_name" : "弹指人生"
]),
([      "action" : "$N一式"GRN"「笑指天南」"NOR"，左掌蓄式，右指弹出一缕指风点向$n的$l",
        "lvl" : 40,
        "skill_name" : "笑指天南"
]),
([      "action" : "$N用出"HIY"「擎天一指」"NOR"，蓄集全身力气，一指点向$n的$l",
        "lvl" : 50,
        "skill_name" : "擎天一指"
]),
});

int valid_enable(string usage) { return usage == "finger" || usage == "throwing" || usage == "parry"; }
int valid_combine(string combo) { return combo=="lanhua-shou"; }
int double_attack() { return 1; }
int valid_learn(object me)
{
        object weapon;

        if( query("int", me)<28 )
                return notify_fail("你若有所悟，然而总是有点不明白。\n");

        if( weapon=query_temp("weapon", me) )
                if( query("skill_type", weapon) != "throwing" )
                        return notify_fail("学弹指神通必须空手或手持暗器。\n");

        if( query("max_neili", me) >= 1000)return 1;

        if ((int)me->query_skill("bibo-shengong", 1) < 70)
                return notify_fail("你的碧波神功火候不够，无法学弹指神通。\n");

        if (me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("修习弹指神通必须有碧波神功配合。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的内力太弱，无法练弹指神通。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( weapon=query_temp("weapon", me) )
                if( query("skill_type", weapon) != "throwing" )
                        return notify_fail("练弹指神通必须空手或手持暗器。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够练弹指神通。\n");

        me->receive_damage("qi", 70);
        addn("neili", -70, me);

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
        int d_e1 = -50;
        int d_e2 = -30;
        int p_e1 = -30;
        int p_e2 = -10;
        int f_e1 = 300;
        int f_e2 = 400;
        int i, lvl, seq, ttl;
        lvl = (int) me->query_skill("tanzhi-shentong", 1);
        if (random(lvl) > 100 && me->query_skill("force") > 120
         && query("neili", me)>200 )
        {
                addn("neili", -50, me);
                if (! weapon)
                        return ([
                                "action": HBRED "$N一声断喝，只听“嗤嗤”之声连响，无数道劲风从四面八方袭向$n" NOR,
                                "damage": 160,
                                "force" : 400,
                                "attack": 200,
                                "dodge" : -100,
                                "parry" : -100,
                                "damage_type": "刺伤",
                        ]);
                else
                        return ([
                                "action":HBRED"$N一声断喝，只听“嗤嗤”之声连响，无数"+query("name", weapon)+HBRED"从四面八方袭向$n"NOR,
                                "damage": 260,
                                "damage": 300,
                                "attack": 200,
                                "dodge" : -100,
                                "parry" : -100,
                                "damage_type": "刺伤",
                                "post_action": (:call_other, WEAPON_D, "throw_weapon":)
                ]);
        }
        if( weapon )
                ttl = sizeof(action_throwing);
        else
                ttl = sizeof(action_finger);

        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 获得招数序号上限 */
                        break;
                }
        seq = random(seq);       /* 选择出手招数序号 */
        if( weapon )
        return ([
                "action"      : action_throwing[seq],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "刺伤" : "瘀伤",
        ]);
        else
        return ([
                "action"      : action_finger[seq],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "刺伤" : "瘀伤",
        ]);
}

string perform_action_file(string action)
{
        return __DIR__"tanzhi-shentong/" + action;
}

mixed hit_ob(object me, object victim, int damage)
{
        string name, weapon;
        mixed result;
        name = xue_name[random(sizeof(xue_name))];

        //if (victim->is_busy()) return 0;

        if( !objectp(weapon=query_temp("weapon", me)) )
        {
                if( (query("neili", me)>200) && me->query_skill("tanzhi-shentong",1)>100
                 && query("max_neili", me)>1200 )
                {
                        if( !victim->is_busy() )
                                victim->start_busy(3);
                        addn("neili", -30, me);
                        if( query("neili", victim) <= (damage/2+30) )
                                set("neili", 0, victim);
                        else
                                addn("neili", -damage/2+30, victim);
                        return HIR "$N突然伸指，连点$n"HIC"「"+name+"」"HIR"，$n脸色陡然变得苍白，内息直泄！\n" NOR;
                }
        } else
        {
                if( (query("neili", me)>200) && me->query_skill("tanzhi-shentong",1)>60 )
                {
                        if( !victim->is_busy() )
                                victim->start_busy(2);
                        addn("neili", -30, me);
                        result = ([ "damage" : damage ]);
                        result += ([ "msg" : HIR "$n被$N的暗器打中"HIC"「"+name+"」"HIR"，内息大乱！\n" NOR]);

                        return result;
                }
        }

}

int query_effect_parry(object attacker, object me)
{
        object weapon;
        int lvl;

        if( objectp(weapon=query_temp("weapon", me)) )
                if( query("skill_type", weapon) != "throwing" )
                        return 0;

        lvl = me->query_skill("tanzhi-shentong", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping prepare;
        string attack_skill;
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("tanzhi-shentong", 1) < 100
         || !living(me) || query_temp("weapon", me) )
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("tanzhi-shentong", 1);

        if( objectp(weapon=query_temp("weapon", ob)) )
                attack_skill=query("skill_type", weapon);
        else
        {
                prepare = ob->query_skill_prepare();
                if (! prepare) prepare = ([]);
                else if (sizeof(prepare) == 0)  attack_skill = "unarmed";
                else if (sizeof(prepare) == 1)  attack_skill = (keys(prepare))[0];
                else if( sizeof(prepare) == 2)attack_skill=(query_temp("action_flag", keys(prepare))[ob)];
        }
        attack_skill = ob->query_skill_mapped(attack_skill);

        if (ap / 2 + random(ap) < dp && stringp(attack_skill))
        {
                result = ([ "damage": -damage ]);
                // 去掉所有的伤害写法
                if( objectp(weapon=query_temp("weapon", ob)) )
                {
                        result += (["msg" : HIC "$n" HIC "伸指一弹，嗤的一声轻响，一股细细的劲力激射出去，"
                                                "登时将" + weapon->name() + HIC"上所附内劲尽数抵销，"
                                                        "化解了这招" + to_chinese(attack_skill) + "。\n" NOR]);
                }
                else    result += (["msg" : HIC "$n" HIC "伸指一弹，嗤的一声轻响，一股细细的劲力激射出去，"
                                "这「弹指神通」与$N的「" + to_chinese(attack_skill) + "」斗了个旗鼓相当，"
                                        "谁也没能伤谁。\n" NOR]);
                return  result;
        }
}

*/


int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n弹指神通："NOR"\n");
        write(@HELP

    东海桃花岛主黄药师的成名绝技。
    可与兰花拂穴手互备。

        学习要求：
                碧波神功20级
                内力100
HELP
        );
        return 1;
}
