// liumang-shenquan.c 流氓神拳
// By Alf, Last Update 2001.11

// 黑虎掏心 双风贯耳 叶底偷桃 独劈华山 二郎担山 拔草寻蛇 猛虎跳涧

#include <ansi.h>
inherit SKILL;
int is_pbsk() { return 1; }

mapping *action = ({
([      "action" : "$N沉腰坐马，左拳护身，右拳直击，一招「黑虎掏心」，挟着风声击向$n的$l",
        "force" : 120,
        "dodge" : 20,
        "parry" : 20,
        "lvl" : 0,
        "skill_name" : "黑虎掏心",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N抢上一步，双拳左右抡开，胸前卖个破绽，一招「双风贯耳」，合击$n的$l",
        "force" : 140,
        "dodge" : 15,
        "parry" : 15,
        "lvl" : 20,
        "skill_name" : "双风贯耳",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身形一矮，左拳虚晃$n面门，右掌一个「叶底偷桃」，望准$n的$l狠命一抓",
        "force" : 160,
        "dodge" : 10,
        "parry" : 10,
        "lvl" : 40,
        "skill_name" : "叶底偷桃",
        "damage_type" : "瘀伤",
]),
([      "action" : "$N将身一长，一招「独劈华山」，呼的一掌去势奇快，当头向$n的$l猛劈过去",
        "force" : 180,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 60,
        "skill_name" : "独劈华山",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N腰杆挺直，脚下前弓后箭，双掌一错，使出一招「二郎担山」，拍向$n的$l",
        "force" : 200,
        "dodge" : -5,
        "parry" : -5,
        "lvl" : 80,
        "skill_name" : "二郎担山",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N步履一沉，一招「拔草寻蛇」，脚下一个扫堂腿横扫，同时出拳捣向$n的$l",
         "force" : 210,
        "dodge" : -5,
        "parry" : -10,
        "lvl" : 90,
        "skill_name" : "拔草寻蛇",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N口里一声怪吼，双拳虚握，状如虎爪，一招「猛虎跳涧」，对准$n的$l抓去",
         "force" : 220,
        "dodge" : -10,
        "parry" : -10,
        "lvl" : 100,
        "skill_name" : "猛虎跳涧",
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练流氓神拳必须空手。\n");

        if( query("max_neili", me)<50 )
                return notify_fail("你的内力太低，无法练流氓神拳。\n");

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
        level = (int) me->query_skill("liumang-shenquan",1);
        
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]) 
                return action[NewRandom(i, 20, level/5)];
                    
}

int practice_skill(object me)
{
        int lvl = me->query_skill("liumang-shenquan", 1);
        int i = sizeof(action);

        return notify_fail("流氓神拳博大精深，无法靠着普通的练习提升。\n"); 

        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if( query("qi", me)<50 )
                return notify_fail("你的体力太低了。\n");
        
        me->receive_damage("qi", 30);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liumang-shenquan/" + action;
}

void skill_improved(object me) 
{
        int lvl = me->query_skill("liumang-shenquan", 1);

        if( lvl > 150 &&
            !query("can_perform/liumang-shenquan/hui", me) ) 
        {
                tell_object(me, HIC "你通晓了流氓神拳「" HIR "流氓会武术" HIC "」的奥秘。\n" NOR);    
                set("can_perform/liumang-shenquan/hui", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
        }

        if( lvl > 200 &&
            !query("can_perform/liumang-shenquan/dang", me) ) 
        {
                tell_object(me, HIC "你通晓了流氓神拳「" HIR "谁也档不住" HIC "」的奥秘。\n" NOR);    
                set("can_perform/liumang-shenquan/dang", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
        }

}
