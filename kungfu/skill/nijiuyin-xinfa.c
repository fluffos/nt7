#include <ansi.h>
inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("nijiuyin-xinfa", 1);
        return lvl * lvl * 15 * 14 / 100 / 200;
}

mapping *action = ({
([      "action" : "$N身形一转，拳头携着疾速旋转的气流挥出，疾如闪电，势如雷霆，击向$n",
        "dodge"  : 50,
        "force"  : 300,
        "attack" : 120,
        "parry"  : 21,
        "damage" : 58,
        "lvl"    : 0,
        "damage_type": "震伤" 
]), 
([      "action" : "$N身形一转，拳头携着疾速旋转的气流挥出，疾如闪电，势如雷霆，击向$n",
        "dodge"  : 50,
        "force"  : 332,
        "attack" : 112,
        "parry"  : 37,
        "damage" : 61,
        "lvl"    : 180,
        "damage_type": "震伤"
]), 
([      "action" : "$N身体一侧，一掌凌空劈出，一股凛冽的气流顿时澎湃涌至$n的$l处",
        "dodge"  : 67,
        "force"  : 360,
        "attack" : 122,
        "parry"  : 53,
        "damage" : 72,
        "lvl"    : 220,
        "damage_type": "震伤"
]),
([      "action" : "$N攻势忽缓而不疏，$w变化无常，捉摸不定向$n慢慢卷去",
        "dodge"  : 75,
        "force"  : 410,
        "attack" : 143,
        "parry"  : 67,
        "damage" : 81,
        "lvl"    : 240,
        "damage_type": "震伤"
]), 
});

int valid_enable(string usage)
{               
                return usage == "force";
}

int valid_force(string force) { return 1; }

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("nijiuyin-xinfa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        int i,skill,damage,lvl;
        
        skill = me->query_skill("nijiuyin-xinfa",1);
        if( query("jing", me)<60 )
                return notify_fail("你的精力太低了。\n");
                
        if( query("qi", me)<200 )
                return notify_fail("你的体力不够练逆九阴心法。\n");
         
        if (me->query_condition("jiuyin-except"))
                return notify_fail("你完全无法控制自已，还哪里有心情去修炼逆九阴心法？\n"); 
        
        if (me->query_skill("jiuyin-shengong", 1) > 1)
        {
                return notify_fail("你已经学会九阴神功了，怎么还能去修炼逆九阴心法？\n");
        }       
        
        if( query("sleep_room", environment(me)) )
                return notify_fail("竟然在这么多人休息的地方练这种武功，你是白痴啊？\n");        
        
        if( skill>100 && query("shen", me)>-100 )
                return notify_fail("这种邪恶武功不是侠义道当练的。\n");
        
        if( query("neili", me)<400 && random(10)<3 )
        {      
                message_vision(HIY "突然你但觉一股无明真气冲至你头顶。随即你只感到全身就像被撕裂般痛苦!\n"NOR,me);         
                me->apply_condition("jiuyin-except", skill + (int)me->query_condition("jiuyin-except"));
                return 1;
        }
        if( query("neili", me)<200 )
        
                return notify_fail("你的内力不够练逆九阴心法。\n");
        
        me->receive_damage("qi", 100);
        me->receive_damage("jing", 20);
        addn("neili", -50, me);
        tell_room(environment(me), 
MAG"只见"+query("name", me)+"双目紧闭，凝神聚气、双手抱圆，头顶不时地冒出一丝丝白气，随之
双手之间形成一股气流，忽然只见"+query("name", me)+"脸色痛苦无比，鲜血由嘴角慢慢逸出。\n");

        return 1;
}

void skill_improved(object me)
{
    tell_object(me, HIR "你忽然从心底生出一股恶念：嘿嘿.....我要成为天下第一......谁敢与我为敌！\n" NOR );
    addn("shen", -100, me);
}
