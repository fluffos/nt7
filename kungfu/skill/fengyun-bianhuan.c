//fengyun-bianhuan.c 风云变幻
//By haiyan

inherit SKILL; 
int is_pbsk() { return 1; }

mapping *action = ({
([      "action":"只见$N脚步变幻不定，身形一晃再晃，一招「无孔不入」，双拳径破$n之防守，痛击$n$l。",
        "force" :100,
        "attack":12,
        "dodge" :30,
        "damage":12,
        "lvl"   :0,
        "skill_name" :"无孔不入",
        "damage_type":"砸伤"
]),
([      "action":"$N暗运真气，双腿便似钉在地上一般，一式「拍案齐掌」，接连五六个直拳一气打向$n$l。",
        "force" :130,
        "attack":20,
        "dodge" :60,
        "damage":26,
        "lvl"   :40,
        "skill_name" :"拍案齐掌",
        "damage_type":"瘀伤"
]),
([      "action":"$N一个横跃而出，使出一招「意欲凌风翔」，两拳向下猛击$n的头部。",
        "force" :150,
        "attack":32,
        "dodge" :80,
        "damage":40,
        "lvl"   :70,
        "skill_name" :"意欲凌风翔",
        "damage_type":"瘀伤"
]),
([      "action":"$N双手平举胸前，使出一招「雷震轩辕」，向前急速推出，击向$n的$l。",
        "force" :180,
        "attack":46,
        "dodge" :110,
        "damage":52,
        "lvl"   :100,
        "skill_name" :"雷震轩辕",
        "damage_type":"瘀伤"
]),
([      "action":"$N右手微拳，探步向左，使出一招「推窗望月」，右手后缩，肘部重重地撞向$n$l。",
        "force" :220,
        "attack":65,
        "dodge" :150,
        "damage":68,
        "lvl"   :150,
        "skill_name" :"推窗望月",
        "damage_type":"内伤"
]),
([      "action":"$N使出「太华夜碧」，脚下步伐窜动，两手在胸前交叉，右拳攻向$n$l。",
        "force" :250,
        "attack":78,
        "dodge" :180,
        "damage":80,
        "lvl"   :180,
        "skill_name" :"太华夜碧",
        "damage_type":"内伤"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_learn(object me)
{
     if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
         return notify_fail("练风云变幻必须空手。\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 100)
         return notify_fail("你的内功心法火候太浅，不能学风云变幻。\n");

     if ((int)me->query_skill("cuff", 1) < 100)
         return notify_fail("你的基本拳法火候不够。\n");

     if( query("max_neili", me)<350 )
         return notify_fail("你的内力太低，无法学风云变幻。\n");

     if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("fengyun-bianhuan", 1))
         return notify_fail("你的基本拳法水平有限，无法领会更高深的风云变幻。\n");

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
     level = (int) me->query_skill("fengyun-bianhuan", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
         return notify_fail("练风云变幻必须空手。\n");

     if( query("qi", me)<100 )
            return notify_fail("你的体力不够练风云变幻。\n");

     if( query("neili", me)<90 )
            return notify_fail("你的内力不够练风云变幻。\n");

     me->receive_damage("qi", 85);
     addn("neili", -65, me);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"fengyun-bianhuan/" + action;
}
