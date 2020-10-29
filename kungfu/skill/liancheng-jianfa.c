// This program is a part of NITAN MudLIB
// liancheng-jian.c 连城剑法

inherit SKILL;

string *action_msg = ({
        "$N使一式「孤鸿海上来」，手中$w嗡嗡微振，幻成一条疾光刺向$n的$l",
        "$N错步上前，使出「池潢不敢顾」，手中$w划出一道剑光劈向$n的$l",
        "$N手中$w一抖，一招「落日照大旗」，斜斜一剑反腕撩出，攻向$n的$l",
        "$N手中剑锵啷啷长吟一声，一式「马鸣风萧萧」，一道剑光飞向$n的$l",
        "$N一式「落日阳关路」，手中$w舞出无数剑花，使$n难断虚实，无可躲避",
        "$N手中$w斜指苍天，剑芒吞吐，一式「羌笛怨杨柳」，对准$n的$l斜斜击出",
        "$N一式「春风度玉门」，手腕急抖，挥洒出万点金光，刺向$n的$l",
        "$N一式「遥挂在前川」，$w飞斩盘旋，如疾电般射向$n的胸口",
        "$N一式「飞流三千尺」，$w突然从天而降，一片金光围掠$n全身",
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me) { return 1; }

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(60),
                "attack": 70 + random(10),
                "dodge" : 20 + random(10),
                "parry" : 20 + random(10),
                "damage_type" : random(2)?"刺伤":"割伤",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
        if( query("qi", me)<80 )
                return notify_fail("你的体力不够练连城剑法。\n");
        if( query("neili", me)<80 )
                return notify_fail("你的内力不够。\n");
        me->receive_damage("qi", 70);
        addn("neili", -70, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liancheng-jianfa/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( !objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("liancheng-jianfa", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}