// 倚天剑法

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action": "$N剑尖剑芒暴长，一招「倚天寒芒」，手中$w大开大阖，剑芒直刺$n的$l",
        "force" : 250,
        "attack": 150,
        "dodge" : 50,
        "parry" : 50,
        "damage": 51,
        "lvl"   : 0,
        "skill_name" : "倚天寒芒",
        "damage_type" : "刺伤"
]),
([      "action": "$N剑芒吞吐，单手$w一招「翻江倒海」，剑势曼妙，剑光直逼向$n的$l",
        "force" : 270,
        "attack": 180,
        "dodge" : 60,
        "parry" : 60,
        "damage": 78,
        "lvl"  : 30,
        "skill_name" : "翻江倒海",
        "damage_type" : "刺伤"
]),
([      "action": "$N一式「神剑佛威」，屈腕云剑，剑光如彩碟纷飞，幻出点点星光飘向$n",
        "force" : 280,
        "attack": 220,
        "dodge" : 80,
        "parry" : 80,
        "damage": 147,
        "lvl"   : 50,
        "skill_name" : "神剑佛威",
        "damage_type" : "刺伤"
]),
([      "action": "$N挥剑分击，剑势自胸前跃出，$w一式「群邪辟易」，毫无留恋之势，刺向$n",
        "force" : 290,
        "attack": 231,
        "dodge" : 81,
        "parry" : 83,
        "damage": 155,
        "lvl"   : 80,
        "skill_name" : "群邪辟易",
        "damage_type" : "刺伤"
]),
([      "action": "$N左手剑指划转，腰部一扭，右手$w一记「荡妖除魔」自下而上刺向$n的$l",
        "force" : 300,
        "attack": 275,
        "dodge" : 95,
        "parry" : 95,
        "damage": 193,
        "lvl"   : 150,
        "skill_name" : "荡妖除魔",
        "damage_type" : "刺伤"
]),
(["action": HIR "$N脸色凝重凝重，缓缓举起$w"NOR""HIR"，突然跃起身剑合一，使出一招“倚天不出”，\n手中$w"NOR""HIR"由下至上划出一条美丽的弧线刺向$n的$l" NOR,
         "damage": 250,
         "attack": 300,
         "dodge": 100,
         "parry": 100,
         "lvl": 150,
         "damage_type": "刺伤",
         "skill_name": "倚天不出",
]),
(["action": HIY "$N反身跃起，双手握剑举至头顶使出倚天剑法奥义“谁与争锋”，这看似简简单单的一剑，\n而厚重的剑气直奔$n的$l而去"NOR,
         "damage": 300,
         "attack": 350,
         "dodge": 120,
         "parry": 120,
         "lvl": 220,
         "damage_type": "刺伤",
         "skill_name": "谁与争锋",
])
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("character", me) == "心狠手辣" ||
            query("character", me) == "阴险奸诈" ||
            query("character", me) == "狡黠多变" )
                return notify_fail("以你的性格不适合修炼此剑术。\n");

        if( query("int", me)<33 )
                return notify_fail("以你的资质永远也学不会倚天剑法。\n");

        if( query("con", me)<28 )
                return notify_fail("以你根骨不适合修炼倚天剑法。\n");

        if( query("max_neili", me)<250 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force", 1) < 50)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("sword", 1) < 50)
                return notify_fail("你的基本剑法火候太浅。\n");

        if (me->query_skill("sword", 1) < me->query_skill("yitian-jian"))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的倚天剑法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yitian-jian", 1);
         for (i = sizeof(action); i > 0; i--)
                 if (level > action[i - 1]["lvl"])
                         return action[NewRandom(i, 5, level / 5)];
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的体力不够练倚天剑法。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的内力不够练倚天剑法。\n");

        me->receive_damage("qi", 50);
        addn("neili", -60, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
         mixed result;
         object weapon;

         if( objectp(weapon) && query("id", weapon) == "yitian jian" )
         {
                victim->receive_damage("qi", damage_bonus+me->query_skill("yitian-jian"), me);
                victim->receive_damage("jing", (damage_bonus+me->query_skill("yitian-jian")) / 2, me);
                return WHT "$N有了倚天剑，顿时剑光大胜，剑气之声连连呼啸而过，$n"
                       WHT "$n只觉气血翻腾，“哇”的吐出一口鲜血。\n" NOR;
         }

         if (damage_bonus < 100)
         {
                 result =  ([ "damage" : damage_bonus / 2]);
                 result += (["msg" : "$n"NOR""HIR"只觉一阵清风拂过，只见"NOR"$n"HIR"的嘴角竟露出一丝血色！\n" NOR]);
                 return result;
         }

         if (damage_bonus > 100)
         {
                 result =  ([ "damage" : damage_bonus ]);
                 result += (["msg" : "$n"NOR""MAG"只觉一阵清风拂过，只见"NOR"$n"MAG"血冒三丈，已被$N的剑气所伤！\n" NOR]);
                 return result;
         }
}


string perform_action_file(string action)
{
        return __DIR__"yitian-jian/" + action;
}