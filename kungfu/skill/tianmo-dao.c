//tianmo-dao.c 天魔刀法
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"$N高高跃起，一式「刀劈乾坤」，向$n$l一劈！",
        "force" :60,
        "attack":18,
        "dodge" :30,
        "parry" :20,
        "damage":25,
        "lvl"   :0,
        "skill_name" :"刀劈乾坤",
        "damage_type":"劈伤"
]),
([      "action":"只见$N倒提$w，身形急冲，就在与$n错身之际，突然使出「昙花一现」从$n后脑斜劈而下。",
        "force" :80,
        "attack":25,
        "dodge" :50,
        "parry" :35,
        "damage":30,
        "lvl"   :30,
        "skill_name" :"昙花一现",
        "damage_type":"劈伤"
]),
([      "action":"$N一式「星河欲曙天」，手中$w化做一道刀光, 似银河倒泻般挥向$n$l。",
        "force" :95,
        "attack":38,
        "dodge" :70,
        "parry" :50,
        "damage":50,
        "lvl"   :60,
        "skill_name" :"星河欲曙天",
        "damage_type":"砍伤"
]),
([      "action":"$N眼神恍惚，手中$w飘摇不定，一招「边风飘摇」斜斜的砍向$n的$l。",
        "force" :110,
        "attack":45,
        "dodge" :90,
        "parry" :75,
        "damage":70,
        "lvl"   :90,
        "skill_name" :"边风飘摇",
        "damage_type":"砍伤"
]),
([      "action":"$N狂喝一声，使出一招「绝域苍茫」，双手紧握$w带着逼人的杀气，刺向$n的$l。",
        "force" :130,
        "attack":62,
        "dodge" :110,
        "parry" :95,
        "damage":85,
        "lvl"   :120,
        "skill_name" :"绝域苍茫",
        "damage_type":"刺伤"
]),
([      "action":"$N斜身飞起，一招「乘风破浪」，带出一片刀光卷向$n的$l。",
        "force" :160,
        "attack":80,
        "dodge" :110,
        "parry" :102,
        "damage":100,
        "lvl"   :150,
        "skill_name" :"乘风破浪",
        "damage_type":"劈伤"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
     object weapon;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "blade" )
         return notify_fail("你必须手里拿着刀才能练刀法。\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 100)
         return notify_fail("你的内功心法火候太浅，不能学天魔刀法。\n");

     if ((int)me->query_skill("blade", 1) < 100)
         return notify_fail("你的基本刀法火候不够。\n");

     if( query("max_neili", me)<350 )
         return notify_fail("你的内力太低，无法学天魔刀法。\n");

     if ((int)me->query_skill("blade", 1) < (int)me->query_skill("tianmo-dao", 1))
         return notify_fail("你的基本刀法水平有限，无法领会更高深的天魔刀法。\n");

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
     level = (int) me->query_skill("tianmo-dao", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     object weapon;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "blade" )
         return notify_fail("你必须手里拿着刀才能练天魔刀法。\n");

     if( query("qi", me)<100 )
            return notify_fail("你的体力不够练天魔刀法。\n");

     if( query("neili", me)<90 )
            return notify_fail("你的内力不够练天魔刀法。\n");

     me->receive_damage("qi", 70);
     addn("neili", -75, me);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"tianmo-dao/" + action;
}
