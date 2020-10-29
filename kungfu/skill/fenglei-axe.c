// fenglei-axe.c 九霄风雷斧 

inherit SKILL;
#include <ansi.h>

string *action_msg = ({
       "$N将$w一摆，先天真气激荡，第一式『春雷乍响』浑然天成，有若实质的气劲如利斧般劈向$n" NOR,
       "$w斧势一变，竟如穿花引蝶般小巧细腻，正是『九霄风雷斧』第九式『阴风藏雨』" NOR,
       "$N大开大阖，第二式『狂风乱云』闪电般劈向$n" NOR,
       "$N暴喝声中$w高举过头，运劲直劈，第四式『天雷焚城』果然绝无半点花俏" NOR,
       "$w再变，从$N肋下穿出，遥击$n的$l，第七式『迅雷千幻』让$n完全无法捉摸来势" NOR,
       "$N手中$w自左而右划了一个大弧，$w借第五式『暴风绞沙』这道弧线泛起层层斧影，向$n平推而至" NOR,
       "$N跃至半空，使出第三式『九霄落雷』，手中$w隐挟雷音，织成一道斧网向$n罩去" NOR,
       "$N凝气守中，$w化大巧为大拙，运劲逼出丈许雪亮斧芒，第六式『疾风骤雨』一斧快似一斧地攻向$n" NOR,
       "$N挥斧由中宫直进，手腕翻处，中途转向，第八式『旱地雷音』早已变换了数个方位，最终劈向$n的$l" NOR,
       "$w自$N手中弹起，化出一道漂亮的弧线劈向$n，同时左手挥拳直击，正是威力最大的第十式『风雷齐至』" NOR,
});

int valid_enable(string usage) { return usage == "axe" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("zidian-jin", 1) < 25)
                return notify_fail("你的玄天紫电劲火候太浅。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 180 + random(50),
                "attack": 100 + random(30),
                "dodge" : 100 + random(30),
                "parry" : 100 + random(30),
                "damage_type" : random(2)?"劈伤":"砍伤",
        ]);
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result; 
        
        if (me->query_skill("zidian-jin", 1) < 100
        ||  me->query_skill_mapped("force") != "fenglei-axe"
         || !query_temp("powerup", me )
        ||  damage < 100) return 0;

        if (random(damage / 2) > 50) 
        {
                result = ([ "damage": damage ]);                 
                result += (["msg" : HIR "只见紫芒闪过，$n鮮血四濺，被$N" HIR "斧上聚集的玄天紫电劲所伤！\n" NOR]);
                return result;
        }
}


int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "axe" )
                return notify_fail("你使用的武器不对。\n");
        if( query("qi", me)<70 )
                return notify_fail("你的体力不够练九霄风雷斧。\n");
        if( query("neili", me)<70 )
                return notify_fail("你的内力不够练九霄风雷斧。\n");               
        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"fenglei-axe/" + action;
}
