// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit SKILL;

string *action_msg = ({
        "$N伫立不动，挥动$w，使出一招「大海沉沙」，手中$w缓缓向$n的$l击去，去势虽不劲急，\n但鞭势沉滞，如同压了几千斤泥沙一般",
        "$N手持$w中央，一招「海天一线」，$w一端陡然一翻，点向$n前胸，劲风所至，将$n退路封住，\n另一端如灵蛇出洞，疾速卷向$n脚踝",
        "$N冷哼一声，急催内力，使出一招「巨浪排空」，鞭势加快，只见十数重鞭影如惊滔骇浪般向$n的$l疾卷而来",
        "$N缓缓转动手中$w，一式「万里无波」，手中$w去势奇慢，不带丝毫破空之声，\n但所过之处尘土飞扬，$w上所带劲风已刮得人扑面生疼",
        "$N身形游走不定，忽地使出一招「沧海一粟」，$w上风声大作，刹那间数十条鞭影从四面八方向$n周身要害击到",
        "$N狂啸一声，双目精光大盛，一招「怒海蓝涛」，鞭势展开，或横扫直击，或盘旋翻卷，倾刻间已将$n全身裹住",
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<50 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("bibo-shengong", 1) < 30)
        {
                return notify_fail("你的碧波神功火候太浅。\n");
        }
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 110 + random(20),
                "attack": 80 + random(10),
                "dodge" : 20 + random(10),
                "parry" : 20 + random(10),
                "damage_type" : random(2)?"鞭伤":"刺伤",
        ]);
}

int practice_skill(object me)
{
        object weapon, where;

        where = environment(me);

        if( !query("guanchao", where) )
                return notify_fail("你练习了一会儿沧浪鞭法，发觉怎么也不能领会沧浪二字的精粹。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不对。\n");
        if( query("qi", me)<60 )
                return notify_fail("你的体力不够练沧浪鞭法。\n");
        message_vision(HIC"$N面对海潮，徐徐挥鞭，使呼吸与海潮同步，渐渐感觉体内真气也如海潮澎湃一般无穷无尽。\n"NOR, me);
        addn("neili", random(3), me);
        me->recieve_damage("qi", 50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"canglang-bian/" + action;
}
