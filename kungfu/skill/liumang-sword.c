
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": HIW "$N大喝一声，一招「流氓霸市」，手中$w平空横扫，一条剑气划向$n的$l" NOR,
        "force" : 25,
        "dodge" : 20,
        "parry" : 25,
        "lvl"   : 0,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N向前跨上一步，右手$w使出一式「雷剑闪」直刺$n的$l" NOR,
        "force" : 30,
        "dodge" : 25,
        "parry" : 30,
        "lvl"   : 6,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N身形往右一挫，右手$w使出一式「冲心剑」刺向$n的$l" NOR,
        "force" : 30,
        "dodge" : 35,
        "parry" : 35,
        "lvl"   : 12,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N双膝下沉，右手$w使出一式「锁喉式」，由下而上疾刺$n的$l" NOR,
        "force" : 35,
        "dodge" : 35,
        "parry" : 40,
        "lvl"   : 15,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N一招「车轮剑」，$w自上而下划出一个大弧，平平地向$n的$l挥去" NOR,
        "force" : 35,
        "dodge" : 45,
        "parry" : 45,
        "lvl"   : 18,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N上身往左侧一拧，一招「恶龙摆尾」，右手$w反手向$n的$l挥去" NOR,
        "force" : 35,
        "dodge" : 45,
        "parry" : 55,
        "lvl"   : 21,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N一招「摧心式」，剑锋平指，一气呵成横扫$n的$l" NOR,
        "force" : 40,
        "dodge" : 60,
        "parry" : 55,
        "lvl"   : 24,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N左腿提膝，手中$w斜指，一招「破目式」刺向$n的$l" NOR,
        "force" : 40,
        "dodge" : 55,
        "parry" : 60,
        "lvl"   : 27,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N一招「回龙式」，$w自下而上划出一个大弧，平平地挥向$n的$l" NOR,
        "force" : 45,
        "dodge" : 65,
        "parry" : 65,
        "lvl"   : 30,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N使出「套月式」，$w划出三个圆圈，剑锋直出，绵绵不断划向$n的$l" NOR,
        "force" : 45,
        "dodge" : 70,
        "parry" : 70,
        "lvl"   : 35,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N一招「卷风式」，$w轻灵地划出几个圆弧，迅速地向$n的$l挥去" NOR,
        "force" : 50,
        "dodge" : 75,
        "parry" : 80,
        "lvl"   : 40,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N一招「抱头式」，$w划出一个左低右高的大弧，斜斜地斩向$n的$l" NOR,
        "force" : 50,
        "dodge" : 75,
        "parry" : 80,
        "lvl"   : 45,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N使出「缠丝式」，$w由右向左划出一个大８字，将$n圈在其中" NOR,
        "force" : 55,
        "dodge" : 85,
        "parry" : 80,
        "lvl"   : 50,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N左脚踏实，右脚虚点，一招「恶人指路」，右手$w带着一团剑花，逼向$n的$l" NOR,
        "force" : 55,
        "dodge" : 95,
        "parry" : 80,
        "lvl"   : 60,
        "damage_type" : "刺伤"
]),
([  "action" : HIC "$N回身拧腰，右手虚抱，一招「天人同灭」，$w中宫直进，刺向$n的$l" NOR,
        "force" : 950,
        "attack": 1140,
        "dodge" : 2220,
        "parry" : 2220,
        "damage": 1140,
        "lvl" : 2500,
        "damage_type" : "刺伤"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本剑法火候太浅。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("liumang-sword", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        object m_weapon;

        if ((int) me->query_skill("liumang-sword", 1) < 100 ||
            !(m_weapon=query_temp("weapon", me)) || 
            query("skill_type", m_weapon) != "sword" )
                return;

        ap = ob->query_skill("force");
        dp = me->query_skill("sword", 1) / 2 +
             me->query_skill("liumang-sword", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "一抖手中的" + m_weapon->name() +
                                            HIC "，划出了一个圆圈，竟然让$N" +
                                            HIC "的攻击全然落空。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "晃动手中的" + m_weapon->name() +
                                            HIC "，不住的变幻剑势，让$N"
                                            HIC "完全无法捕捉到力道。\n" NOR]);
                        break;
                }
                return result;
        }
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        me->receive_damage("qi", 50);
        addn("neili", -64, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liumang-sword/" + action;
}