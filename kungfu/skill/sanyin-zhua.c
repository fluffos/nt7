//sanyin-zhua.c 三阴蜈蚣抓
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action" : "$N爪现青白，骨结隆起，自上而下撕扯$n的$l",
    "force" : 120,
    "dodge" : 10,
    "damage": 30,
    "damage_type" : "抓伤"
]),
([  "action" : "$N双手忽隐忽现，爪爪鬼魅般抓向$n的$l",
    "force" : 150,
    "dodge" : 20,
    "damage": 45,
    "lvl"   : 30,
    "damage_type" : "抓伤"
]),
([  "action" : "$N身形围$n一转，爪影纵横毫不留情对着$n的$l抓下",
    "force" : 180,
    "dodge" : 30,
    "damage": 55,
    "lvl"   : 60,
    "damage_type" : "抓伤"
]),
([  "action" : "$N一声怪叫，一爪横出直击$n的$l",
    "force" : 240,
    "dodge" : 50,
    "damage": 60,
    "lvl"   : 90,
    "skill_name" : "唯我独尊" ,
    "damage_type" : "抓伤"
]),
([  "action" : "$N两眼邪光闪动，身子飘飘忽忽，抽身探出一爪猛然击向$n的$l",
    "force" : 270,
    "dodge" : 60,
    "damage": 90,
    "lvl"   : 120,
    "skill_name" : "唯我独尊" ,
    "damage_type" : "抓伤"
]),
});

int valid_enable(string usage) { return usage == "claw" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "chousui-zhang"; }

int valid_learn(object me)
{
        
        int  nb,  nh;
        nb = (int)me->query_skill("poison", 1);
        nh = (int)me->query_skill("sanyin-zhua", 1);

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练三阴蜈蚣爪必须空手。\n");
                
        if ((int)me->query_skill("huagong-dafa", 1) < 10)
                return notify_fail("你的化功大法火候不够，无法学三阴蜈蚣爪。\n");
                
        if ( nb < 100 && nb <= nh )
                return notify_fail("你的毒技修为不够，无法提高三阴蜈蚣爪。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的内力太弱，无法练三阴蜈蚣爪。\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if (level >= action[i - 1]["lvl"])
                        return action[i - 1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("sanyin-zhua", 1);
        for(i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];

}

int practice_skill(object me)
{
        int  nb,  nh; 
        nb = (int)me->query_skill("poison", 1); 
        nh = (int)me->query_skill("sanyin-zhua", 1); 

        if (nb < 100 && nb <= nh) 
                return notify_fail("你的毒技修为不够，无法提高三阴蜈蚣爪。\n"); 

        if( query("qi", me)<50 )
                return notify_fail("你的体力太低了。\n");
                
        if( query("neili", me)<50 )
                return notify_fail("你的内力不够练三阴蜈蚣爪。\n");
                
        me->receive_damage("qi", 40);
        addn("neili", -40, me);
        
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("sanyin-zhua", 1);
        flvl=query("jiali", me);

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("xx_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIW "$n" HIW "只感一阵极寒从心底升起，看来是中了$N" HIW "抓上的剧毒。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"sanyin-zhua/" + action;
}