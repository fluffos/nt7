// huzhua-gong.c 虎爪功

#include <combat.h>
#include <ansi.h>


inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N双爪一张，斜身进步，脚踏中宫，一式「黑虎掏心」，疾如迅电，锐不可挡，向$n胸口猛拍过去",
        "force" : 100,
        "attack": 30,
        "dodge" : 25,
        "parry" : 5,
        "damage": 10,
        "lvl"   : 0,
        "skill_name" : "黑虎掏心" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N身形骤起，双臂箕张，向外一展，一招「猛虎下山」，双爪翻飞，自上而下，罩向$n天灵",

        "force" : 120,
        "attack": 41,
        "dodge" : 30,
        "parry" : 5,
        "damage": 30,
        "lvl"   : 10,
        "skill_name" : "猛虎下山" ,
        "damage_type" : "内伤"
]),
([      "action": "$N让过来势，竟用一式「饿虎扑食」，合身扑上，如疾风般，欺到$n身前，罩向$n周身各处大穴",
        "force" : 120,
        "attack": 55,
        "dodge" : 45,
        "parry" : 30,
        "damage": 65,
        "lvl"   : 40,
        "skill_name" : "饿虎扑食" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N运足真气，震声长啸，正是一式「虎啸东山」，在$n一愕之间，已欺身进前，猛扳$n双腕",
        "force" : 170,
        "attack": 64,
        "dodge" : 36,
        "parry" : 18,
        "damage": 70,
        "lvl"   : 60,
        "skill_name" : "虎啸东山" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N微微一闪，一招「大虫卷尾」，反圈到$n身后，疾如飘风，直朝$n肩后抓去",
        "force" : 180,
        "attack": 77,
        "dodge" : 58,
        "parry" : 5,
        "damage": 80,
        "lvl"   : 80,
        "skill_name" : "大虫卷尾" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N如影随形，跟踪直上，正是一式「巨虎穿林」，身随掌走，掌随身转，朝$n面门袭去",
        "force" : 220,
        "attack": 87,
        "dodge" : 42,
        "parry" : 22,
        "damage": 95,
        "lvl"   : 100,
        "skill_name" : "巨虎穿林" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N双足一蹬，一跃而起，半空中使出一式「龙腾虎跃」，携翻身捣海之势，风雷夹击之声，向$n抓去",
        "force" : 250,
        "attack": 85,
        "dodge" : 40,
        "parry" : 29,
        "damage": 110,
        "lvl"   : 120,
        "skill_name" : "龙腾虎跃" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N往后一闪，一式「病虎藏身」，让过对方攻势，右爪悄然探出，抓向$n腰眼",
        "force" : 300,
        "attack": 96,
        "dodge" : 75,
        "parry" : 45,
        "damage": 107,
        "lvl"   : 140,
        "skill_name" : "病虎藏身" ,
        "damage_type" : "抓伤"
])
});

int valid_enable(string usage) { return usage == "claw" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "qinna-shibada"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练虎爪功必须空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，无法学虎爪功。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力太弱，无法练虎爪功。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("huzhua-claw"))
                return notify_fail("你的基本爪法火候水平有限，无法领会更高深的虎爪功。\n");

        if ((int)me->query_skill("jimie-zhua", 1) < (int)me->query_skill("huzhua-claw"))

                return notify_fail("你的寂灭爪火候水平有限，无法领会更高深的虎爪功。\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i - 1]["lvl"])
                        return action[i - 1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("huzhua-claw", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手练习！\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够练虎爪功。\n");

        if ((int)me->query_skill("jiemie-zhua", 1) < (int)me->query_skill("huzhua-claw", 1))
                return notify_fail("你的寂灭爪火候水平有限，无法领会更高深的虎爪功。\n");

        me->receive_damage("qi", 60);
        addn("neili", -75, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huzhua-claw/" + action;
}
