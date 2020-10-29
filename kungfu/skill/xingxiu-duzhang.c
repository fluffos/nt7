// Updated by Lonely
// xingxiu-duzhang.c, based on xianglong-zhang.c
// by yucao
// Ryu, 12/4/96.
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N脸上露出诡异的笑容，隐隐泛出绿色的双掌扫向$n的$l",
        "dodge": -30,
        "force": 280,
//      "poison": 80,
        "damage_type": "瘀伤"
]),
([      "action": "$N突然身形旋转起来扑向$n，双掌飞舞着拍向$n的$l",
        "dodge": -10,
        "force": 200,
//      "poison": 60,
        "damage_type": "瘀伤"
]),
([        "action": "$N将毒质运至右手，一招「腐尸毒」阴毒无比地抓向$n的$l",
        "dodge": -20,
        "force": 450,
        "damage": 65,
//      "poison": 100,
        "damage_type": "瘀伤"
]),
([        "action": "$N双掌挟着一股腥臭之气拍向$n的$l",
        "dodge": -10,
        "force": 350,
        "damage": 60,
//      "poison": 80
        "damage_type": "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="sanyin-zhua"; }
mapping query_action(object me)
{
        mapping a_action;
        int i, level;
        level = (int) me->query_skill("xingxiu-duzhang",1);
        if (random(me->query_skill("strike")) > 60 &&
            me->query_skill("force") > 50 &&
            query("neili", me)>100){
                addn("neili", -100, me);
                return ([
                "action":BLU "$N咬破舌尖，口中喷血，聚集全身的力量击向$n"NOR,
                "force": 480,
                "attack": 300,
                "parry" :-300,
                "dodge" :-300,
                "damage": 80,
                "damage_type": "内伤"]);
        }
        for( i = sizeof(action); i > 0; i-- )
                if( level > action[i-1]["lvl"] )
                {
                        a_action = action[NewRandom(i, 20, level/5)];
                        break;
                }
        a_action["dodge"] -= level / 10;
        a_action["parry"] = level / 10;
        a_action["force"] += level / 10;
        a_action["damage"] += level / 10;
        return a_action;
}

int valid_learn(object me)
{
        int  nb,  nh;
        nb = (int)me->query_skill("poison", 1);
        nh = (int)me->query_skill("xingxiu-duzhang", 1);

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练星宿毒掌必须空手。\n");
        if ((int)me->query_skill("huagong-dafa", 1) < 10)
                return notify_fail("你的化功大法火候不够，无法练星宿毒掌。\n");
        if ( nb < 100 && nb <= nh )
                return notify_fail("你的毒技修为不够，无法提高星宿毒掌。\n");

        if( query("max_neili", me)<60 )
                return notify_fail("你的内力太弱，无法练星宿毒掌");
        return 1;
}


int practice_skill(object me)
{
        int  nb,  nh;
        nb = (int)me->query_skill("poison", 1);
        nh = (int)me->query_skill("xingxiu-duzhang", 1);

        if( query("jingli", me)<30 )
                return notify_fail("你的精力太低了。\n");
        if( query("neili", me)<8 )
                return notify_fail("你的内力不够练星宿毒掌。\n");
        if ( nb < 100 && nb <= nh )
                return notify_fail("你的毒技修为不够，无法提高星宿毒掌。\n");

        if (me->query_skill("xingxiu-duzhang", 1) < 50)
                me->receive_damage("jingli", 20);
        else
                me->receive_damage("jingli", 30);
        addn("neili", -5, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if( random(me->query_skill("xingxiu-duzhang", 1)) > 30 ) {
                victim->apply_condition("xx_poison", 
                random(me->query_skill("xingxiu-duzhang", 1)/2) + victim->query_condition("xx_poison"));
        }
}
string perform_action_file(string action)
{
        if ( this_player()->query_skill("xingxiu-duzhang", 1) >= 30 )
                return __DIR__"xingxiu-duzhang/" + action;
}