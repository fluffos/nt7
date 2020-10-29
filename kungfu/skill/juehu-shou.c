// juehu-shou.c -
// updated by Lonely

inherit SKILL;

mapping *action_msg = ({
        "$N一式「老牛拉车」，以掌化爪，五指如钩，两眼瞪得通红，直逼$n的裆部",
        "$N四肢贴地，头部底垂，看似已无力进攻，突然四肢用力一扒已窜到$n跨下，两手猛的上戳，好一式「精疲力尽」",
        "$N两手高高举起，运掌如风，一式「壮士断腕」，闭眼就朝$n的下体砍去",
        "$N一跃而起，直往$n的双肩落下，双腿盘住$n的颈部，一扭腰，双手成关门之势，往$n的裆部狠狠拍去，正是一式「落叶归根」",
        "$N使一式「空前绝后」，身形一分为二，四只手掌有如熊掌般朝$n的后腰和裆部拍去",
        "$N全身关节啪啪作响，面如白纸，一式「断子绝孙」，无数鹰爪抓向$n全身要害，瞬间无数鹰爪又合为一爪直往$n的裆部抓落",
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练虎抓绝户手必须空手。\n");
                
        if ((int)me->query_skill("taiji-shengong", 1) < 40)
        
                return notify_fail("你的太极神功火候不够，无法学虎抓绝户手。\n");
                
        if( query("max_neili", me)<100 )
                return notify_fail("你的内力太弱，无法练虎抓绝户手。\n");
                
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(20),
                "attack": 60 + random(10),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "damage_type" : random(2)?"抓伤":"瘀伤",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的内力不够练虎抓绝户手。\n");
        me->receive_damage("qi", 25);
        addn("shen", -10, me);
        addn("neili", -10, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"juehu-shou/" + action;
}

