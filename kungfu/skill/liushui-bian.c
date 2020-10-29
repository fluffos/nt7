//liushui-bian.c 流水鞭法
//By haiyan

inherit SKILL; 

int is_pbsk() { return 1; }
mapping *action = ({
([      "action":"只见$N身形疾转，手腕轻抖，一式「天地双飞」，$w在身畔化作两道飞虹。",
        "force" :180,
        "dodge" :10,
        "attack":30,
        "damage":50,
        "lvl"   :0,
        "skill_name" :"天地双飞",
        "damage_type":"割伤"
]),
([      "action":"$N一式「荒烟平楚」，手中$w吞吐不定，仿佛一层轻烟薄雾飘上$n肩头，若即若离。",
        "force" :190,
        "dodge" :50,
        "attack":45,
        "damage":80,
        "lvl"   :10,
        "skill_name" :"荒烟平楚",
        "damage_type":"割伤"
]),
([      "action":"$N力贯$w，一招「芦花飘香」点点鞭影飘浮不定地点向$n的$l。",
        "force" :210,
        "dodge" :80,
        "attack":60,
        "damage":110,
        "lvl"   :80,
        "skill_name" :"芦花飘香",
        "damage_type":"刺伤"
]),
([      "action":"$N徐徐舞动$w，却是一招「似真似幻」，只见招断意连，缠绵婉转，一鞭未绝，便隐隐有万鞭相随。",
        "force" :230,
        "dodge" :110,
        "attack":85,
        "damage":130,
        "lvl"   :110,
        "skill_name" :"似真似幻",
        "damage_type":"割伤"
]),
([      "action":"$N一式「千山暮雪」，$w挥洒自如，霎时间绛雪纷纷，娇如柳絮，弱似梨花，密密裹住$n全身。",
        "force" :250,
        "dodge" :140,
        "attack":120,
        "damage":150,
        "lvl"   :150,
        "skill_name" :"千山暮雪",
        "damage_type":"刺伤"
]),
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
     object weapon;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "whip" )
         return notify_fail("你必须先找一条鞭子才能练鞭法。\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 150)
         return notify_fail("你的内功心法火候太浅，不能学流水鞭法。\n");

     if ((int)me->query_skill("whip", 1) < 150)
         return notify_fail("你的基本鞭法火候不够。\n");

     if( query("max_neili", me)<500 )
         return notify_fail("你的内力太低，无法学流水鞭法。\n");

     if ((int)me->query_skill("whip", 1) < (int)me->query_skill("liushui-bian", 1))
         return notify_fail("你的基本鞭法水平有限，无法领会更高深的流水鞭法。\n");

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
     level = (int) me->query_skill("liushui-bian", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     object weapon;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "whip" )
         return notify_fail("你必须先找一条鞭子才能练鞭法。\n");

     if( query("qi", me)<110 )
            return notify_fail("你的体力不够练流水鞭法。\n");

     if( query("neili", me)<115 )
            return notify_fail("你的内力不够练流水鞭法。\n");

     me->receive_damage("qi", 92);
     addn("neili", -98, me);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"liushui-bian/" + action;
}
