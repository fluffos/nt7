// huanmo-longtianwu.c 幻魔胧天舞

inherit SKILL;

mapping *action = ({
([      "action":"$N左掌微分，右手一伸，扣向$n的$l。",
        "force" :10,
        "dodge" :10,
        "damage":10,
        "lvl"   :0,
        "damage_type" :"瘀伤"
]),
([      "action":"$N倏地一个转身，双手一翻，直掼$n下颌。",
        "force" :20,
        "dodge" :15,
        "damage":20,
        "lvl"   :10,
        "damage_type" :"瘀伤"
]),
([      "action":"$N身子一纵，双手滑溜异常对准$n的后心抓去。",
        "force" :35,
        "dodge" :30,
        "damage":30,
        "lvl"   :25,
        "damage_type" :"瘀伤"
]),
([      "action":"$N左手虚晃，右手飘飘，拍向$n$l",
        "force" :50,
        "dodge" :40,
        "damage":40,
        "lvl"   :40,
        "damage_type" :"瘀伤"
]),
([      "action":"$N身形微动，晃至$n身后，双手变爪，直袭$n后脑。",
        "force" :70,
        "dodge" :60,
        "damage":55,
        "lvl"   :60,
        "damage_type" :"瘀伤"
])
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_combine(string combo) { return combo=="xuwu-piaomiao"; }

int valid_learn(object me)
{ 
    if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
        return notify_fail("练幻魔胧天舞必须空手。\n"); 

    if ((int)me->query_skill("force", 1) < 60)
        return notify_fail("你的内功火候不够，无法学幻魔胧天舞。\n"); 

    if( query("max_neili", me)<250 )
        return notify_fail("你的内力太弱，无法练幻魔胧天舞。\n"); 

    if ((int)me->query_skill("hand", 1) < (int)me->query_skill("huanmo-longtianwu", 1)) 
        return notify_fail("你的基本手法火候不够，无法领会更高深的幻魔胧天舞。\n"); 

    return 1;
}

mapping query_action(object me, object weapon) 
{ 
    int i, level; 
    level = (int)me->query_skill("huanmo-longtianwu", 1);
    for(i = sizeof(action); i > 0; i--) 
        if(level > action[i-1]["lvl"]) 
             return action[NewRandom(i, 20, level/5)]; 
} 

int practice_skill(object me) 
{ 
    if( query("qi", me)<45 )
         return notify_fail("你的体力太低了。\n"); 

    if( query("neili", me)<35 )
         return notify_fail("你的内力不够练「幻魔胧天舞」。\n"); 

    me->receive_damage("qi", 28); 
    addn("neili", -20, me);

    return 1; 
}
