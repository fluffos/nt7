// shenlong-sword.c 神龙剑法

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action":"$N使一式「"+BLK+"潮泛银海"+NOR+"」，手中$w疾挽，漫天寒光，隐夹风雷之声，闪电般狂涌向$n的$l",
        "force" : 120,
        "lvl" : 0,
        "skill_name" : BLK "潮泛银海" NOR,
        "damage_type":  "割伤"
]),
([      "action":"$N错步上前，使出「"+RED+"银雨飞花"+NOR+"」，手中$w登时剑芒暴射，宛如漫天瑞雪飞洒向$n的$l",
        "force" : 140,
        "lvl" : 20,
        "skill_name" : RED "银雨飞花" NOR,
        "damage_type":  "割伤"
]),
([      "action":"$N手中$w一抖，一招「"+GRN+"花影滨飞"+NOR+"」，$w犹如狂风扫落叶般急攻向$n的$l",
        "force" : 160,
        "lvl" : 34,
        "skill_name" : GRN "花影滨飞" NOR,
        "damage_type":  "割伤"
]),
([      "action":"$N手中$w锵啷啷长吟一声，一式「"+BLU+"神龙寻食"+NOR+"」，$w头上脚下洒攻而下，攻势之疾，无以伦比向$n的$l",
        "force" : 180,
        "lvl" : 47,
        "skill_name" : BLU "神龙寻食" NOR,
        "damage_type":  "刺伤"
]),
([      "action":"$N一式「"+MAG+"西风倒卷"+NOR+"」，手中$w将剑自下拖上，端的无比毒辣使$n难断虚实，无可躲避",
        "force" : 220,
        "lvl" : 60,
        "skill_name" : MAG "西风倒卷" NOR,
        "damage_type":  "刺伤"
]),
([      "action":"$N手中$w,一式「"+BLU+"天罗地网"+NOR+"」，仿佛一面无形的黑网向$n的$l斜斜击出",
        "force" : 260,
        "lvl" : 80,
        "skill_name" : BLU "天罗地网" NOR,
        "damage_type":  "刺伤"
]),
([      "action":"$N一式「"+HIR+"日月失色"+NOR+"」，$w银光万道，如江河倒泻，剑芒绵绵无尽向$n的胸口递去",
        "force" : 380,
        "lvl" : 110,
        "skill_name" : HIR "日月失色" NOR,
        "damage_type":  "刺伤"
]),
([      "action":"$N一式「"+YEL+"金针渡劫"+NOR+"」，$w形神合一，把全部真气贯注剑身之上，快如天光乍闪向$n刺去",
        "force" : 380,
        "lvl" : 150,
        "skill_name" : HIY "金针渡劫" NOR,
        "damage_type":  "刺伤"
])
});
int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int practice_level(){   return 150;  }
int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
        || query("skill_type", weapon) != "sword" )
                if( !objectp(weapon=query_temp("secondary_weapon", me) )
                || query("skill_type", weapon) != "sword" )
                        return notify_fail("你必须先弄把剑才能学神龙剑法。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force", 1) < 40)
                return notify_fail("你的基本内功火候太浅。\n");

        if (me->query_skill("sword", 1) <= me->query_skill("shenlong-jian",1))
                return notify_fail("你的基础不够，无法领会更高深的技巧。\n");

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
        level   = (int) me->query_skill("shenlong-jian",1);


        for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
                  return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
        || query("skill_type", weapon) != "sword" )
                if( !objectp(weapon=query_temp("secondary_weapon", me) )
                || query("skill_type", weapon) != "sword" )
                        return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的体力不够练神龙剑。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的内力不足以练神龙剑。\n");

        me->receive_damage("qi", 25);
        addn("neili", -20, me);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"shenlong-jian/" + action;
}


