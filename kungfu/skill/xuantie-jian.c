// This program is a part of NT MudLIB

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *msg = ({
BLU "$N当胸平平刺出一剑，实在是毫无任何变化，而却有轰轰之声，$n"BLU"只觉\n一股大力由$w"BLU"直逼周身",
BLU "$N凌空跃起，身随剑起，借助下行之势向下猛劈一剑，将$n"BLU"周身笼于剑气之下",
BLU "$N轻叹一声，随手横劈一剑，缓缓指向$n"BLU"，看似无丝毫变化，却尽得剑\n法精髓，当真平淡中蕴涵所有变化，无招胜有招",
BLU "$N迅疾挑出一剑，但见剑势如虹，快似闪电，无可当锋！此剑之快，匪夷所\n思，$n"BLU"无法分辨出剑路去来",
BLU "$N仰首长啸，令风云变幻，狂风遽起，旋及一剑平指，剑气弥漫于$n"BLU"周\n身各处，$n"BLU"只觉身处惊涛骇浪之中，惊怖中更觉$N剑力有如海潮一般，一波\n一浪阵阵涌来，绵延不绝，愈发愈强",
BLU "$N祭起$w"BLU"，左手捏成剑诀置于胸前，咄喝一声，正是剑法至尊的“御剑\n式”，空中满是剑影，宛若千道银链，只在$n"BLU"身边游动",
BLU "$N$w"BLU"连出十余剑，一时迅疾如流星划空，一时凝重迟缓，招招无迹可寻，\n平淡至极又匪思至极，顺刺，逆击，横削，倒劈，无不是剑法的入门，当真返朴\n归真，却已不再存任何破绽",
});

mapping *action = ({
([      "action": "$N手中的$w荡出，就如大江东去，威力势不可挡",
        "force" : 250,
        "attack": 170,
        "dodge" :-30,
        "parry" :-70,
        "damage": 230,
        "lvl"   : 0,
        "damage_type": "割伤"
]),
([      "action": "$N踏上一步，手中$w舞出一道剑光劈向$n的$l",
        "force" : 310,
        "attack": 280,
        "dodge" :-33,
        "parry" :-79,
        "damage": 224,
        "lvl"   : 40,
        "damage_type": "割伤"
]),
([      "action": "$N手中$w一抖，一剑刺出，攻向$n的$l，没有半点花巧",
        "force" : 330,
        "attack": 290,
        "dodge" :-41,
        "parry" :-85,
        "damage": 235,
        "lvl"   : 80,
        "damage_type": "割伤"
]),
([      "action": "$N手中$w微微颤动，忽然刺出，一道剑光射向$n的$l",
        "force" : 360,
        "attack": 295,
        "dodge" :-45,
        "parry" :-92,
        "damage": 239,
        "lvl"   : 120,
        "damage_type": "刺伤"
]),
([      "action": "$N横过$w，蓦然横扫$n，气势如虹，荡气回肠",
        "force" : 340,
        "attack": 297,
        "dodge" :-47,
        "parry" :-99,
        "damage": 248,
        "lvl"   : 160,
        "damage_type": "割伤"
]),
([      "action": "$N手中的$w连削带刺，夹带着一阵旋风掠过$n全身",
        "force" : 380,
        "attack": 300,
        "dodge" :-50,
        "parry" :-100,
        "damage": 300,
        "lvl"   : 200,
        "damage_type": "刺伤"
])
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{

        if( query("str", me)<26 )
                return notify_fail("你的先天膂力孱弱，无法学习玄铁剑法。\n");

        if( query("character", me) == "心狠手辣" )
                return notify_fail("你一心想杀尽敌人，没能理解玄铁剑法的的真正含义。\n");

        if( query("character", me) == "阴险奸诈" )
                return notify_fail("你一心想怎么学好剑法去害人，结果没能理解玄铁剑法。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的内功火候不到，无法学习玄铁剑法。\n");

        if (me->query_skill("martial-cognize", 1) < 50)
                return notify_fail("你武学修养不足，无法领悟玄铁剑法！\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力太差，无法学习玄铁剑法。\n");

        if (me->query_skill("force", 1) < me->query_skill("xuantie-jian", 1))
                return notify_fail("你的基本内功水平有限，无法领会更高深的玄铁剑法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("xuantie-jian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的玄铁剑法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("xuantie-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;
        object env;

        env = environment(me);
        if( !query("can_practice_xiantie-jian", env) &&
            me->query_skill("xuantie-jian", 1) < 180)
                return notify_fail("你拿起剑挥舞了半天，只觉得此处不适合练习玄铁剑法。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的体力不够练玄铁剑法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够练玄铁剑法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -70, me);

        if( query("can_practice_xiantie-jian", env) )
        message_vision(HIW "\n$N" HIW"屏气凝息，挥舞着手中的"+ weapon->name() + HIW "，奋力与洪流相抗。\n\n", me);

        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon=query_temp("weapon", me);

        lvl = me->query_skill("xuantie-jian", 1);

        if (damage_bonus < 120
           || lvl < 160
           || ! objectp(weapon)
           || query("neili", me)<500
           || me->query_skill_mapped("sword") != "xuantie-jian" )
                      return damage_bonus / 4;

        //if (lvl / 2 + random(lvl) > victim->query_skill("parry", 1))
        {
                addn("neili", -120, me);
                victim->receive_wound("qi", damage_bonus * 4 / 5, me);

                return HIW "$N" HIW "手中" + weapon->name() + HIW "犹如神助，从天而下，威不"
                       "可挡地劈向$n" HIW "，气势恢弘之极。\n" NOR;
         }
}

int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
        return __DIR__"xuantie-jian/" + action;
}
int query_effect_parry(object attacker, object me)
{
        object weapon;
        int lvl;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return 0;

        lvl = me->query_skill("xuantie-jian", 1);
        if (lvl < 90)  return 0;
        if (lvl < 100) return 50;
        if (lvl < 125) return 55;
        if (lvl < 150) return 60;
        if (lvl < 175) return 65;
        if (lvl < 200) return 70;
        if (lvl < 225) return 75;
        if (lvl < 250) return 80;
        if (lvl < 275) return 90;
        if (lvl < 325) return 100;
        if (lvl < 350) return 110;
        return 120;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me)) ||
                query("id", weapon) != "ironsword" )
                return 0.8;
        else return 1.2;
}