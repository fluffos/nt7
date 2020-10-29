//xiuli-qiankun.c

inherit SHAOLIN_SKILL; 

mapping *action = ({ 
  ([      "action" : "$N一式「童子拜佛」，双袖隆起，一道无边暗劲涌向$n", 
    "force" : 200, 
    "dodge" : 5, 
    "parry" : 0,
    "damage": 10, 
    "lvl" : 9, 
    "skill_name" : "童子拜佛", 
    "damage_type" : "瘀伤" 
  ]),
  ([      "action" : "$N身形突转，双袖飞舞，霎时间拍出千百道掌影，正是一招「烟雨飘渺」，令$n无可躲藏", 
    "force" : 230, 
    "dodge" : 15, 
    "parry" : 10, 
    "damage": 10, 
    "lvl" : 29, 
    "skill_name" : "烟雨飘渺",
    "damage_type" : "瘀伤" 
  ]),
  ([      "action" : "$N双袖一引一收，掌劲却至下而上斜斜击出，一式「回风舞柳」，$n待要避时已然不及", 
    "force" : 270, 
    "dodge" : 5,
    "parry" : 15,
    "damage": 20, 
    "lvl" : 39, 
    "skill_name" : "回风舞柳",
    "damage_type" : "瘀伤" 
  ]),
  ([      "action" : "只见$N双袖一摆，陡然滑出数尺，右掌顺著来势一招「桃坟扑蝶」往$n的$l按去",
    "force" : 320, 
    "dodge" : 10,
    "parry" : 5, 
    "damage": 15,
    "lvl" : 49, 
    "skill_name" : "桃坟扑蝶", 
    "damage_type" : "瘀伤" 
  ]),
  ([      "action" : "$N身形陡进，罡阳柔气从袖底挥出，涌向$n的$l，正是玄功若神的一招「晓阳云暖」",
    "force" : 380, 
    "dodge" : 25,
    "parry" : -5,
    "damage": 25,
    "lvl" : 59, 
    "skill_name" : "晓阳云暖",
    "damage_type" : "瘀伤" 
  ]),
  ([      "action" : "$N长吸一口真气，身形一振，一式「佛动山河」，双掌当胸平推而出，看似缓慢，$n却已无法闪避！",
    "force" : 420, 
    "dodge" : 15, 
    "parry" : 0, 
    "damage": 35,
    "lvl" : 69,
    "skill_name" : "佛动山河", 
    "damage_type" : "瘀伤" 
  ]),
  ([      "action" : "$N猛地门户大开，迎着$n的掌势合身而上，掌劲及身的一霎那，$N突然一个鹞子翻身，电光火石间$n的掌力已然全部返回，正是少林不传之密「乾坤逆转」", 
    "force" : 480, 
    "dodge" : 20, 
    "parry" : 10, 
    "damage": 50, 
    "lvl" : 80, 
    "skill_name" : "乾坤逆转", 
    "damage_type" : "瘀伤" 
  ]) 
}); 
int valid_enable(string usage) { return  usage=="unarmed" || usage=="parry"; } 
int valid_combine(string combo) { return combo=="hunyuan-zhang"; } 
int valid_learn(object me) 
{ 
    if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
        return notify_fail("练袖里乾坤须空手。\n"); 
    if ((int)me->query_skill("shaolin-xinfa", 1) < 100) 
        return notify_fail("你的少林心法不够，无法学习袖里乾坤。\n"); 
    if( query("max_neili", me)<1500 )
        return notify_fail("你的内力太弱，无法练习袖里乾坤。\n"); 
    return 1; 
} 
mapping query_action(object me, object weapon) 
{ 
    int i, level; 
    level   = (int)me->query_skill("xiuli-qiankun",1); 
    for(i = sizeof(action); i > 0; i--) 
        if(level > action[i-1]["lvl"]) 
            return action[NewRandom(i, 20, level/5)]; 
} 
int practice_skill(object me) 
{
    if( query("qi", me)<30 )
        return notify_fail("你的体力太低了。\n"); 
    if( query("neili", me)<20 )
        return notify_fail("你的内力不够练习袖里乾坤。\n"); 
    me->receive_damage("qi", 30); 
    addn("neili", -10, me);
    return 1;
}
string perform_action_file(string action) 
{ 
    return __DIR__"xiuli-qiankun/" + action; 
}