#include <ansi.h>
inherit SKILL;

mapping *action = ({

([      "action": "$N使一式「人间道」，手中$w嗡嗡微振，幻成一条疾光刺向$n的$l",
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,
        "skill_name" : "人间道",
        "damage_type": "刺伤"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{

        // 与12T冲突
        if( me->query_skill("yinyang-shiertian",1) && !query("thborn/ok", me) )
                return notify_fail("你感觉体内的阴阳九转真气跌宕起伏，似乎容纳这种技能。\n");
                
        if( query("str", me)<32 )
                return notify_fail("你先天臂力不足。\n");

        if( query("int", me)<32 )
                return notify_fail("你先天悟性不足。\n");

        if( query("dex", me)<32 )
                return notify_fail("你先天身法不足。\n");
                
        if( query("con", me)<32 )
                return notify_fail("你先天根骨不足。\n");                        
                
        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力修为不够，难以修炼人间道。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功火候太浅，难以修炼人间道。\n");

        if ((int)me->query_skill("sword", 1) < 300)
                return notify_fail("你的剑法根基不足，难以修炼人间道。\n");
    
        if ((int)me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("你的武学修养不足，难以修炼人间道。\n");
                    
        if ((int)me->query_skill("buddhism", 1) < 200)
                return notify_fail("你的禅宗心法修为不足，难以修炼人间道。\n");
                                            
        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("renjian-dao", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的人间道。\n");
                                                                
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("renjian-dao", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        if (me->query_skill("renjian-dao", 1) > 180)
                return notify_fail("人间道博大精深，无法简单的通过练习进步。\n");
        return 1;                
}

int difficult_level()
{
        return 30000;
}

string main_skill() { return "lunhui-sword"; } 