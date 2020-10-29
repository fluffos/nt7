inherit SKILL;

#include <ansi.h>

int is_ultimate_skill() { return 1; }

string *parry_msg = ({
        HIY "$N" HIY "招式虽猛，$n" HIY "毫无闪避之意，反手一刀横空而出，竟将这招化解。\n" NOR,
        HIY "$n" HIY "连劈数刀，刀气如虹，$N" HIY "赶紧收招，不敢再进。\n" NOR,
});

mapping *action = ({
([      "action" : "$N手中$w横空扫过，一招「断波无流」，夹杂着呼天抢地般的气势向$n$l砍去",
        "skill_name" : "断波无流",
        "force"  : 500,
        "attack" : 360,
        "parry"  : 100,
        "damage" : 600,
        "damage_type" : "割伤",
]),
([      "action" : "$N一招「神刀无情」，心中一阵凄苦，双眼微闭，$w无情般的划过，挥向$n的$l",
        "skill_name" : "神刀无情",
        "force"  : 500,
        "attack" : 360,
        "parry"  : 100,
        "damage" : 600,
        "damage_type" : "割伤",
]),
([      "action" : "$N使出一招「碧波神刀」，$w犹如海啸般，铺天盖地卷向$n",
        "skill_name" : "碧波神刀",
        "force"  : 500,
        "attack" : 360,
        "parry"  : 100,
        "damage" : 600,
        "damage_type" : "割伤",
]),
([      "action" : "$N一招「沧海横流」，手中$w轻转，化作一道刀芒，横空而出，劈向$n",
        "skill_name" : "沧海横流",
        "force"  : 500,
        "attack" : 360,
        "parry"  : 100,
        "damage" : 600,
        "damage_type" : "割伤",
]),
([      "action" : "$N手拖$w，转身跃起，一招「天刀八式」，$w一声长鸣，八道白光射向$n的$l",
        "skill_name" : "天刀八式",
        "force"  : 600,
        "attack" : 360,
        "parry"  : 100,
        "damage" : 600,
        "damage_type" : "割伤",
]),
([      "action" : "$N一声长叹，回首旧事，心中一阵凄凉，一招「惊天刀煞」使出，$w发出震天般响声，犹如鬼怪般涌向$n",
        "skill_name" : "惊天刀煞",
        "force"  : 600,
        "attack" : 360,
        "parry"  : 200,
        "damage" : 600,
        "damage_type" : "割伤",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("str", me)<38 )
                return notify_fail("你先天臂力不足，无法修炼霸刀。\n");

        if( query("con", me)<38 )
                return notify_fail("你先天臂力不足，无法修炼霸刀。\n");

        if( query("reborn/times", me) < 3 )
                return notify_fail("你转世次数不够，无法领悟霸刀的精髓。\n");

        if( me->query_skill("sword",1) && query("reborn/times", me) < 3 )
                return notify_fail("你所学的杂学太多了，无法专心研习霸刀。\n");

        if( me->query_skill("club",1) && query("reborn/times", me) < 3 )
                return notify_fail("你所学的杂学太多了，无法专心研习霸刀。\n");
                
        if( me->query_skill("staff",1) && query("reborn/times", me) < 3 )
                return notify_fail("你所学的杂学太多了，无法专心研习霸刀。\n");
                
        if( me->query_skill("whip",1) && query("reborn/times", me) < 3 )
                return notify_fail("你所学的杂学太多了，无法专心研习霸刀。\n");
                
        if( me->query_skill("dagger",1) && query("reborn/times", me) < 3 )
                return notify_fail("你所学的杂学太多了，无法专心研习霸刀。\n");
                
        if( me->query_skill("hammer",1) && query("reborn/times", me) < 3 )
                return notify_fail("你所学的杂学太多了，无法专心研习霸刀。\n");
                                                          
        if( query("max_neili", me)<20000 )
                return notify_fail("你的内力修为不足。\n");

        if ((int)me->query_skill("force", 1) < 500)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 500)
                return notify_fail("你的武学修养不足。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("badao", 1))
                return notify_fail("你的基本刀法火候不够，无法领会更高深的霸刀。\n");  
                
        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("badao", 1))
                return notify_fail("你的基本轻功水平有限，无法领会更高深的霸刀。\n");  
                              
        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("badao", 1))
                return notify_fail("你的基本招架水平有限，无法领会更高深的霸刀。\n"); 
                
        if ((int)me->query_skill("force", 1) < (int)me->query_skill("badao", 1))
                return notify_fail("你的基本内功水平有限，无法领会更高深的霸刀。\n"); 
                
        if ((int)me->query_skill("martial-cognize", 1) < (int)me->query_skill("badao", 1))
                return notify_fail("你的武学修养有限，无法领会更高深的霸刀。\n"); 
/*
        // 学会了第三刀必须要求易筋经
        if( query("can_perform/badao/san", me) )
        {
                if ((int)me->query_skill("yijinjing", 1) * 3 < (int)me->query_skill("badao", 1))
                {
                        return notify_fail("你易筋经修为不足，强行提升恐怕会走火入魔。\n");
                }
        }
  */      
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
        return action[random(sizeof(action))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int double_attack()
{
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("霸刀博大精深，无法简单的通过练习进步。\n");
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string *desc;
        object weapon;
        
        weapon=query_temp("weapon", me);
        
        if (! objectp(weapon))return damage_bonus;
        
        desc = ({
                HIY "$N" HIY "纵身而起，举起手中" + weapon->name() + HIY "从天劈下，犹如一道闪电划向$n" HIY "。\n" NOR,
                HIC "$N" HIC "轻旋" + weapon->name() + HIC "，单刀直劈，招式简单之极，却刚猛无比。\n" NOR,
                HIR "$N" HIR "挥动手中" + weapon->name() + HIR "，顿时飞沙走石，夹杂着凌厉的刀势，将$n" HIR "笼罩。\n" NOR,
        });

        if (me->is_busy() 
           || random(4) >= 1
           || ! living(victim) 
           || damage_bonus < 150 
            || query("neili", me)<500
           || me->query_skill("badao", 1) < 500) 
                return 0; 

        // 追加特效
        victim->receive_wound("qi", damage_bonus / 4, me);

        if (random(6) == 1)victim->start_busy(3 + random(5));
        
        return desc[random(sizeof(desc))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp, cost;

        if ((int)me->query_skill("badao", 1) < 350
           || me->query_skill_mapped("parry") != "badao"
            || query("neili", me)<200
           || ! living(me) || random(5) > 2)
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        ap = ob->query_skill("force", 1) * 4 + ob->query_skill("martial-cognize", 1);
        dp = me->query_skill("badao", 1) * 5 + me->query_skill("martial-cognize", 1) + 100;

        if (dp / 2 + random(dp / 2) >= ap)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "毫无留恋，顺势一刀，硬将$N" HIG "逼退。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIG "$n" HIG "不退不闪，连劈数刀，$N" HIG "惊骇之下，连忙收招。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "横刀向前，势与$N" HIG "共存亡，举手反劈，竟将$N" HIG "招式化解 。\n" NOR]);
                        break;
                }
                return result;
        }
}

void skill_improved(object me)  
{ 
        int lvl;
        
        lvl = me->query_skill("badao", 1); 

        if( lvl >= 500 && 
            !query("can_perform/badao/daosha", me) )  
        { 
                tell_object(me, HIC "你通晓了霸刀「" HIR "刀煞" HIC "」的奥秘。\n" NOR);     
                set("can_perform/badao/daosha", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 500 && 
            !query("can_perform/badao/gui", me) )  
        { 
                tell_object(me, HIC "你通晓了霸刀「" HIR "归海一刀" HIC "」的奥秘。\n" NOR);     
                set("can_perform/badao/gui", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 
        
        if( lvl >= 500 && 
            !query("can_perform/badao/juan", me) )  
        { 
                tell_object(me, HIC "你通晓了霸刀「" HIR "龙卷风" HIC "」的奥秘。\n" NOR);     
                set("can_perform/badao/juan", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 1500 && 
            !query("can_perform/badao/hun", me) )  
        { 
                tell_object(me, HIC "你通晓了霸刀「" HIR "刀魂" HIC "」的奥秘。\n" NOR);     
                set("can_perform/badao/hun", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 
} 

string perform_action_file(string action)
{
        return __DIR__"badao/" + action;
}

int difficult_level()
{
        return 30000;
}

