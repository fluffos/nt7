#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N身法迅捷，连出两剑，分袭$n面门和$w，正是一招「横空出世」",
        "force"  : 70,
        "dodge"  : 20,
        "parry"  : 25,
        "attack" : 10,
        "damage" : 35,
        "lvl"    : 0,
        "damage_type" : "刺伤",
        "skill_name"  : "横空出世"
]),
([      "action" : "$N以剑画弧，前脚跨出，一式「风扫落叶」，横剑砍向$n$l，",
        "force"  : 110,
        "dodge"  : 40,
        "parry"  : 40,
        "attack" : 20,
        "damage" : 45,
        "lvl"    : 25,
        "damage_type" : "砍伤",
        "skill_name"  : "风扫落叶"
]),
([     
        "action" : "$N手中$w斜出，径直指向$n$l，正是一招「气冲云霄」",
        "force"  : 160,
        "dodge"  : 30,
        "parry"  : 45,
        "attack" : 30,
        "damage" : 55,
        "lvl"    : 50,
        "damage_type" : "刺伤",
        "skill_name"  : "气冲云霄"
]),
([      
        "action" : "$N手中$w忽地转动，一式「引火上身」，已顺势刺向$n$l",
        "force"  : 180, 
        "dodge"  : 45,
        "parry"  : 50,
        "attack" : 35,
        "damage" : 60,
        "lvl"    : 75,
        "damage_type" : "刺伤",
        "skill_name"  : "引火上身"
]),
([      
        "action" : "$N长啸一声，单脚点地，忽地跃起，挺剑刺向$n$l，正是一招「雁回祝融」",
        "force"  : 240,
        "dodge"  : 80,
        "parry"  : 60,
        "attack" : 45,
        "damage" : 80,
        "lvl"    : 100,
        "damage_type" : "刺伤",
        "skill_name"  : "雁回祝融"
]),
});

string main_skill()
{
        return "wushen-jian";
}

int valid_learn(object me)
{
            object ob; 

        if (me->query_skill("wushen-jian", 1) > 0)
                return notify_fail("你已演练合成了衡山五神剑，不必再单独学习。\n");

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("你必须先找一把剑才能练剑法。\n");
  
            if( query("max_neili", me)<800 )
                return notify_fail("你的内力不够，没有办法练祝融剑法。\n");

        if ((int)me->query_skill("sword", 1) < 120)
                return notify_fail("你的基本剑法太差，没有办法练祝融剑法。\n");

            if (me->query_skill("sword", 1) < me->query_skill("zhurong-jian", 1))
                return notify_fail("你的基本剑法火候有限，无法领会更高深的祝融剑法。\n");

            return 1;
}

int valid_enable(string usage)
{
            return usage == "sword" || usage == "parry";
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

        level = (int) me->query_skill("zhurong-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
            object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

               if( query("neili", me)<65 )
                       return notify_fail("你的内力不足，没有办法练习祝融剑法。\n");

        if( query("qi", me)<65 )
                return notify_fail("你的体力不够练祝融剑法。\n");

            me->receive_damage("qi", 55);
            addn("neili", -60, me);
            return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zhurong-jian/" + action;
}

void skill_improved(object me)
{
        int lvl;

        lvl = me->query_skill("zhurong-jian", 1);
   

        if( lvl > 160 &&
            !query("can_perform/zhurong-jian/wan", me) ) 
        {
                tell_object(me, WHT "你通晓了祝融剑法「" HIC "万剑焚云" WHT "」的奥秘。\n" NOR);    
                set("can_perform/zhurong-jian/wan", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
}

