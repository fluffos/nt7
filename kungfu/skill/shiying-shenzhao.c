//shiying-shenzhao.c 弑鹰神爪
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"$N右手在$n$l划过，随後一招「鹰爪捉食」左爪又向同一方位抓到。",
        "force" :100,
        "attack":12,
        "dodge" :40,
        "damage":15,
        "lvl"   :0,
        "skill_name" :"鹰爪捉食",
        "damage_type":"抓伤"
]),
([      "action":"$N吐气扬声，一招「心随鹰飞灭」双手奔$n的头颈抢去。",
        "force" :120,
        "attack":20,
        "dodge" :60,
        "damage":26,
        "lvl"   :20,
        "skill_name" :"心随鹰飞灭",
        "damage_type":"抓伤"
]),
([      "action":"$N运起内功，一招「千疮百孔」，身子腾空而起，双爪齐向$n面门抓去。",
        "force" :150,
        "attack":35,
        "dodge" :70,
        "damage":40,
        "lvl"   :50,
        "skill_name" :"千疮百孔",
        "damage_type":"抓伤"
]),
([      "action":"$N一招「翼若搏鹰」，屈腿越起，斜飞向右，左手力贯五指，飞快地抓向$n头顶。",
        "force" :180,
        "attack":50,
        "dodge" :85,
        "damage":45,
        "lvl"   :80,
        "skill_name" :"翼若搏鹰",
        "damage_type":"抓伤"
]),
([      "action":"忽听$N一声轻叱，一招「穿针引线」，左手划了个半弧，右手闪电般抓向$n的$l。",
        "force" :200,
        "attack":75,
        "dodge" :100,
        "damage":60,
        "lvl"   :150,
        "skill_name" :"穿针引线",
        "damage_type":"抓伤"
]),
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_learn(object me)
{
     if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
         return notify_fail("练弑鹰神爪必须空手。\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 100)
         return notify_fail("你的内功心法火候太浅，不能学弑鹰神爪。\n");

     if ((int)me->query_skill("claw", 1) < 100)
         return notify_fail("你的基本爪法火候不够。\n");

     if( query("max_neili", me)<350 )
         return notify_fail("你的内力太低，无法学弑鹰神爪。\n");

     if ((int)me->query_skill("claw", 1) < (int)me->query_skill("shiying-shenzhao", 1))
         return notify_fail("你的基本爪法水平有限，无法领会更高深的弑鹰神爪。\n");

     return 1;
}

string query_skill_name(int level)
{
     int i;
     for(i = sizeof(action)-1; i >= 0; i--)
     if(level >= action[i]["lvl"])
            return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
     int i, level;
     level = (int) me->query_skill("shiying-shenzhao", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
//   object weapon;

     if( query_temp("weapon", me) || 
         query_temp("secondary_weapon", me) )
            return notify_fail("练弑鹰神爪必须空手。\n");

     if( query("qi", me)<70 )
            return notify_fail("你的体力不够练弑鹰神爪。\n");

     if( query("neili", me)<80 )
            return notify_fail("你的内力不够练弑鹰神爪。\n");

     me->receive_damage("qi", 65);
     addn("neili", -68, me);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"shiying-shenzhao/" + action;
}