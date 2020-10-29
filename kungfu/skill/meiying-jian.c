//meiying-jian 魅影剑法
// Made by deaner
#include <ansi.h>
inherit SKILL;

int is_pbsk() { return 1; }
mapping *action = ({
([  "action" : "$N手中$w虚晃了数下，跟着猛然刺向$n的$l，去势疾若闪电",
    "force" : 60,
    "damage":100,
    "dodge" : 20,
    "lvl"   : 60,
    "skill_name" : "无中生有",
    "damage_type" : "刺伤"
]),
([  "action" : "$N手中的$w不住的颤动，看似指向$n的$l，忽又改挑$n的$l",
    "force"  : 80,
    "dodge"  : 35,
    "damage" : 100,
    "lvl"    : 100,
    "skill_name" : "鬼影重重",
    "damage_type" : "刺伤"
]),
([  "action" : "$N手中的$w连连晃动，去向变幻不定，最后突然直刺$n的$l",
    "force"  : 100,
    "dodge"  : 55,
    "damage" :100,
    "lvl"    : 140,
    "skill_name" : "如鬼似魅",
    "damage_type" : "刺伤"
]),
([  "action" : "$N手中的$w猛然缩回身侧，随即刺向$n的$l，去势凶猛异常",
    "force"  : 120,
    "dodge"  : 75,
    "damage" : 100,
    "lvl"    : 160,
    "skill_name" : "化虚为实",
    "damage_type" : "刺伤"
]),
([  "action" : "$N滑步错身，手中$w一沉一收，跟着斜斜挥出，疾挑$n的$l",
    "force"  : 140,
    "dodge"  : 90,
    "damage" : 100,
    "lvl"    : 200,
    "skill_name" : "压露啼烟",
    "damage_type" : "刺伤"
]),
([  "action" : "$N大喝一声，手中$w陡然幻出漫天光影，闪电般刺向$n的$l",
    "force"  : 160,
    "dodge"  : 100,
    "damage" : 100,
    "lvl"    : 220,
    "skill_name" : "扫月拂云",
    "damage_type" : "刺伤"
]),
([  "action" : "$N斜跨两步，旋即回身发力，手中$w斜斜刺出，攻向$n的$l",
    "force"  : 170,
    "dodge"  : 120,
    "damage" : 100,
    "lvl"    : 260,
    "skill_name" : "星光密射",
    "damage_type" : "刺伤"
]),
([  "action" : "$N身形一变，手中$w忽地出击，迅疾无比的向$n$l直刺过去",  
    "force"  : 180,
    "dodge"  : 150,
    "damage" : 100,
    "lvl"    : 300,
    "skill_name" : "风驰电掣",
    "damage_type" : "刺伤"
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; } 

int valid_learn(object me)
{
    if( query("max_neili", me)<2500 )
        return notify_fail("你的内力不够。\n");

    if ((int)me->query_skill("force") < 200)
        return notify_fail("你的内功心法火候太浅。\n");

    if ((int)me->query_skill("dodge") < 200)
        return notify_fail("你的轻功火候太浅。\n");

    if ((int)me->query_dex() < 40)
        return notify_fail("你的后天身法还不够灵活。\n");

    return 1;
}

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
        if(level >= action[i]["lvl"])
            return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("meiying-jian",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if (me->query_skill("meiying-jian", 1) >= 400)
        return notify_fail("以你目前的修为只能通过研究该技能才能再有所提高。\n");

    if( !objectp(weapon=query_temp("weapon", me) )
     || query("skill_type", weapon) != "sword" )
        return notify_fail("你使用的武器不对。\n");

    if( query("qi", me)<100 )
        return notify_fail("你的体力不够练魅影剑法。\n");

    if( query("neili", me)<100 )
        return notify_fail("你的内力不够练魅影剑法。\n");

    me->receive_damage("qi", 80);
    addn("neili", -80, me);

    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"meiying-jian/" + action;
}
