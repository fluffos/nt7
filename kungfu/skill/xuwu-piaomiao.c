// xuwu-piaomiao.c 虚无缥缈拳

inherit SKILL;
int is_pbsk() { return 1; }

mapping *action = ({
([      "action":"$N左掌虚按，右拳下击，直奔$n的$l而去。",
        "force" :50,
        "parry" :8,
        "dodge" :10,
        "damage":5,
        "lvl"   :0,
        "damage_type" :"瘀伤"
]),
([      "action":"$N大步跨前，立右拳，挽左拳向$n的$l击去。",
        "force" :55,
        "parry" :10,
        "dodge" :15,
        "damage":10,
        "lvl"   :15,
        "damage_type" :"瘀伤"
]),
([      "action":"$N连踏上两步，双拳飞击$n头部两侧。",
        "force" :65,
        "parry" :10,
        "dodge" :10,
        "damage":20,
        "lvl"   :25,
        "damage_type" :"瘀伤"
]),
([      "action":"$N收拳腰间，晃到$n身后，「呼」地挥出一拳,击向$n的$l。",
        "force" :80,
        "parry" :30,
        "dodge" :20,
        "damage":35,
        "lvl"   :40,
        "damage_type" :"瘀伤"
]),
([      "action":"$N退身侧步，让过$n，右拳反击$n后腰。",
        "force" :100,
        "parry" :40,
        "dodge" :30,
        "damage":40,
        "lvl"   :50,
        "damage_type" :"瘀伤"
]),
([      "action":"$N左拳划过$n右臂，右拳向$n肩头拍了下去。",
        "force" :130,
        "parry" :30,
        "dodge" :20,
        "damage":50,
        "lvl"   :70,
        "damage_type" :"瘀伤"
]),
([      "action":"$N轻轻一纵，身体倒转，双拳向$n脑后击出。",
        "force" :170,
        "parry" :50,
        "dodge" :80,
        "damage":70,
        "lvl"   :80,
        "damage_type" :"瘀伤"
])
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_combine(string combo) { return combo=="huanmo-longtianwu"; }

int valid_learn(object me)
{ 
    if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
        return notify_fail("练虚无缥缈必须空手。\n"); 

    if ((int)me->query_skill("force", 1) < 50) 
        return notify_fail("你的内功火候不够，无法学虚无缥缈。\n"); 

    if( query("max_neili", me)<250 )
        return notify_fail("你的内力太弱，无法练虚无缥缈。\n"); 

    if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("xuwu-piaomiao", 1))
        return notify_fail("你的基本拳法火候不够，无法领会更高深的虚无缥缈。\n");

    return 1;
}

mapping query_action(object me, object weapon) 
{ 
    int i, level; 
    level = (int)me->query_skill("xuwu-piaomiao", 1);
    for(i = sizeof(action); i > 0; i--) 
        if(level > action[i-1]["lvl"]) 
             return action[NewRandom(i, 20, level/5)]; 
} 

int practice_skill(object me) 
{ 
    if( query("qi", me)<50 )
         return notify_fail("你的体力太低了。\n"); 

    if( query("neili", me)<40 )
         return notify_fail("你的内力不够练「虚无缥缈」。\n"); 

    me->receive_damage("qi", 30); 
    addn("neili", -20, me);

    return 1; 
}
