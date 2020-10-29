inherit FORCE;
#include <ansi.h>

mapping *action = ({
([      "action" : "$N身形一转，拳头携着疾速旋转的气流挥出，疾如闪电，势如雷霆，击向$n",
        "dodge"  : 50,
        "force"  : 300,
        "attack" : 100,
        "parry"  : 21,
        "damage" : 160,
        "lvl"    : 0,
        "damage_type": "震伤" 
]), 
([      "action" : "$N身形一转，拳头携着疾速旋转的气流挥出，疾如闪电，势如雷霆，击向$n",
        "dodge"  : 50,
        "force"  : 332,
        "attack" : 112,
        "parry"  : 37,
        "damage" : 200,
        "lvl"    : 100,
        "damage_type": "震伤"
]), 
([      "action" : "$N身体一侧，一掌凌空劈出，一股凛冽的气流顿时澎湃涌至$n的$l处",
        "dodge"  : 67,
        "force"  : 360,
        "attack" : 122,
        "parry"  : 53,
        "damage" : 250,
        "lvl"    : 150,
        "damage_type": "震伤"
]),
([      "action" : "$N双腿微曲，右掌平伸，左掌运起蛤蟆功劲力，呼的一声推向$n",
        "dodge"  : 50,
        "force"  : 332,
        "attack" : 152,
        "parry"  : 37,
        "damage" : 200,
        "lvl"    : 200,
        "damage_type": "震伤"
]), 
([      "action" : "$N闭眼逼住呼吸，猛跃而起，眼睛也不及睁开，便向$n推了出去",
        "dodge"  : 67,
        "force"  : 360,
        "attack" : 202,
        "parry"  : 53,
        "damage" : 300,
        "lvl"    : 220,
        "damage_type": "震伤"
]),
([      "action" : "$N攻势忽缓而不疏，$w变化无常，捉摸不定向$n慢慢卷去",
        "dodge"  : 75,
        "force"  : 410,
        "attack" : 243,
        "parry"  : 67,
        "damage" : 350,
        "lvl"    : 250,
        "damage_type": "震伤"
]), 
});

int valid_enable(string usage)
{ 
        int lvl = (int)this_player()->query_skill("jiuyin-hamagong", 1);

        if (lvl >= 200)    
                return usage == "force" || usage == "unarmed" || usage == "parry";
        else
                return usage == "force";
       
}

string main_skill()
{
        return "jiuyin-hamagong";

}
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("jiuyin-hamagong", 1);
        return lvl * lvl * 15 * 16 / 100 / 200;
}


mapping sub_skills = ([
        "nijiuyin-xinfa" : 250, 
        "hama-gong" : 250,            
        ]);

int valid_learn(object me)
{
        if( query("character", me) == "光明磊落" )
                return notify_fail("你心中暗道：这九阴蛤蟆功阴毒异常，估计会伤及自"
                                   "身，还是别练为妙。\n");
                                   
        if( query("gender", me) == "无性" )
                return notify_fail("你无根无性，阴阳不调，难以领会高深的九阴蛤蟆功。\n");
        if ((int)me->query_skill("jiuyin-hamagong", 1) < 240)
                return notify_fail("你对九阳蛤蟆功理解还不够深。想来想去总想不通!\n"); 

        if ((int)me->query_skill("poison", 1) < 250)
                return notify_fail("你的基本毒技火候不足，难以领会蛤蟆功。\n");        
                
        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("jiuyin-hamagong", 1))
                return notify_fail("你的基本拳脚水平有限，难以领会更高深的九阴蛤蟆功。\n"); 

        if( query("max_neili", me)<4300 )
                return notify_fail("你现在的内力修为不足，难以领会九阴蛤蟆功。\n");

        if( query("str", me)<30 )
                return notify_fail("你先天膂力不够，无法领悟九阴蛤蟆功。\n");
                
        if( query("con", me)<34 )
                return notify_fail("你先天根骨不够，无法领悟九阳蛤蟆功。\n");

        if ((int)me->query_skill("force", 1) < 250)
                return notify_fail("你的基本内功火候还不够，还不能学习九阳蛤蟆功。\n");

        return ::valid_learn(me);
}

int get_finish(object me)
{
        object ob;

        if( query("gender", me) == "无性" )
        {
                tell_object(me, "你演练完毕，只感气血上涌，看来自己阴阳不调，无法演练九阴蛤蟆功。\n" NOR);
                return 0;
        }

        if( query("character", me) == "光明磊落" )
        {
                tell_object(me, "你演练完毕，觉得九阴蛤蟆功邪气纵横，气度狡黠，自己怎么也无法将其合一。\n" NOR);
                return 0;
        }

        if( query("character", me) == "狡黠多变" )
        {
                tell_object(me, "你演练完毕，觉得九阴蛤蟆功邪气纵横，气度狡黠，自己怎么也无法将其合一。\n" NOR);
                return 0;
        }

        if( query("con", me)<34 )
        {
                tell_object(me, "你演练完毕，发现自己的先天根骨太差，无法将九阴蛤蟆功内的武功合一。\n");
                return 0;
        }

        if( query("str", me)<30 )
        {
                tell_object(me, "你演练完毕，发现自己的先天膂力孱弱，无法将九阴蛤蟆功内的武功合一。\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 250)
        {
                tell_object(me, "你觉得九阴蛤蟆功内的武功都极其深奥，看来多研究一下学问可能更有帮助。\n");
                return 0;
        }
        
        if (me->query_skill("jiuyin-shengong", 1) > 1)
        {
                tell_object(me, "你已经学会九阴神功了，怎么都不能逆转成功。\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 190)
        {
                tell_object(me, "你演练完毕，发现自己的武学修养尚待提高，暂且无法将九阴蛤蟆功内的武功合一。\n");
                return 0;
        }

        if( query("max_neili", me)<4500 )
        {
                tell_object(me, "你觉得自己真气不继，无法继续演练九阴蛤蟆功。\n");
                return 0;
        }

        if (random(10) < 6)
        {
                tell_object(me, "你觉得有所感悟，或许再演练一次就能融会贯通，将二者合一。\n");
                return 0;
        }

        tell_object(me, HIW "一阵凡尘往事涌上心头，你默念九阴蛤蟆功，一股莫名的真气由两足涌至头部百汇穴。\n"
                        "不由心意零乱，随即两手撑地，双脚倒立向上，“嘎”一声长呜，声音犹若蛙叫。响彻天地。\n"
                        "蛙呜数声后，你但觉全身无比舒畅!似乎功力比以往提升了数倍!\n" NOR);
        CHANNEL_D->do_channel(me,"rumor",sprintf("忽然%s“嘎”一声长呜，声音犹若蛙叫,响彻天地。",query("name", me)));
        CHANNEL_D->do_channel(me,"rumor",sprintf("%s因祸得福经历万难，终于逆转经脉领悟出西毒欧阳峰不传秘技九阴蛤蟆功了。",query("name", me)));
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int practice_skill(object me)
{
        return notify_fail("九阴蛤蟆功只能用学(learn)的来增加熟练度。\n");
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("jiuyin-hamagong", 1);

        if (damage_bonus < 150
           || lvl < 200
            || query("neili", me)<300
           || me->query_skill_mapped("force") != "jiuyin-hamagong"
           || me->query_skill_mapped("unarmed") != "jiuyin-hamagong"
           || me->query_skill_prepared("unarmed") != "jiuyin-hamagong")
                return 0;

        if (damage_bonus / 4 > victim->query_con())
        {
                addn("neili", -40, me);
                victim->receive_wound("qi", (damage_bonus - 100) / 2, me);
                return WHT "只见$N" HIR "“嘎”"NOR"" WHT "一声长呜，随即疾速扑至身前，全力击出一掌$n始料不及\n"
                       "这一掌如此突然，只能硬接此招，霎时全身一颤，经脉受震，喷出一口鲜血！\n" NOR;
        }
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("jiuyin-hamagong", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

string perform_action_file(string action)
{
        return __DIR__"jiuyin-hamagong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"jiuyin-hamagong/exert/" + action;
}

