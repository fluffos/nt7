#include <ansi.h>
inherit FORCE;

int is_ultimate_skill() { return 1; }
string *dodge_msg = ({
        HIW "$n" HIW "身前一道剑光闪过，竟与剑光合为一体，$N" HIW "目瞪口呆，一时难以找出其间破绽。\n" NOR,
        HIW "只见$n" HIW "以气御剑，剑中生剑，顿时，无数剑影令$N" HIW "眼花缭乱，无从攻击。\n" NOR,
        HIW "$n" HIW "运气内功，呵气成剑，以神御剑，剑花乍现将将$N" HIW "团团围住，哪里还有机会攻击。\n" NOR,
});

string *parry_msg = ({
        HIG "$N" HIG "一招攻出，$n" HIG "不退不避，无数剑芒飞射而出，将此招竟数化解与无形。\n" NOR,
        HIG "$n" HIG "面露微笑，身体猛然间幻化为一把气剑，任$N" HIG "怎样攻击都无法伤之毫厘。\n" NOR,
        HIG "$n" HIG "不慌不忙，手中剑光在面前画出一道优美的弧线，竟将$N" HIG "攻势全部化解。\n" NOR,
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("lunhui-sword", 1);
        return lvl * lvl / 100 * 15 * 38  / 200;
}

int query_jingli_improve(object me)
{
        int lvl;
        
        lvl = (int)me->query_skill("lunhui-sword", 1);
        
        if (me->query_skill_mapped("force") == "lunhui-sword")
                return lvl * 14 / 10;

        return 0;
}

mapping *action = ({
([      "action": HIW "$N" HIW "使出「天极道」，剑法华丽无比，幻化出满天星光，突然间漫天剑式化为一剑，刺向$n" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,
        "skill_name" : "天极道",
        "damage_type": "刺伤"
]),
([      "action": HIM "$N手中$w" HIM "犹如兰花乍现，发出嗡嗡的响声，一式「人间道」使出，顿时幻象重生将$n" HIM "包围" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,        
        "skill_name" : "人间道",
        "damage_type": "割伤"
]),
([      "action": HIG "$N" HIG"一剑划破长空，「饿鬼道」使出，剑光四射，飞向$n" HIG "，攻势凶猛无比，令人生畏" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 450,    
        "skill_name" : "饿鬼道",
        "damage_type": "割伤"
]),
([      "action": HIR "$N" HIR "轻舞剑花，使出「地狱道」，一股寒气自$w" HIR "而出，似野鬼，似离魂，呼啸般涌向$n" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,
        "lvl"   : 300,        
        "skill_name" : "地狱道",
        "damage_type": "割伤"
]),
([      "action": HIC "$N" HIC "催动内力，一式「修罗道」道，刹时剑气狂奔，空气令人窒息，剑气已经袭向$n" HIC "$l" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,       
        "skill_name" : "修罗道",
        "damage_type": "刺伤"
]),
([      "action": HIY "$N" HIY "高举$w" HIY "，剑芒吞吐不定，一式「畜生道」使出，剑气夹杂着惊天地怒吼，犹狂风般袭向$n" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,        
        "skill_name" : "畜生道",
        "damage_type": "刺伤"
]),
([      "action": HIY "$N" HIY "面露微笑，挽出一个剑花，一式「" HIR "六道轮回" HIY "」使出，剑花花瓣顿时化作六色剑芒射向$n",
        "force" : 700,
        "attack": 650,
        "dodge" : 110,
        "parry" : 650,
        "damage": 650,
        "skill_name" : "六道轮回",
        "damage_type": "刺伤"
]),
});

int valid_force(string force)
{
        return 1;
}

int double_attack()
{
        return 1;
}

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry" || usage == "dodge" || usage == "parry" || usage == "force";
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

string main_skill()
{
        return "lunhui-sword";
}

mapping sub_skills = ([
        "tianji-dao"  : 500,
        "diyu-dao"    : 500,
        "egui-dao"    : 500,
        "chusheng-dao": 500,
        "renjian-dao" : 500,
        "xiuluodao"   : 500,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;
        ob = environment(me);

        // 带面具无法演练
        if( query_temp("apply/mask_flag", me) )
        {
                tell_object(me, "你必须先取下面具。\n");
                return 0;
        }

/*
        if( !query("lunhui", ob) )
        {
                tell_object(me, "演练六道轮回剑必须在轮回司中，需要借助轮回之力。\n");
                return 0;
        }
*/
        
        if( query("reborn/times", me) < 3 )
        {
                tell_object(me, "你转世次数不够，无法领悟轮回的精髓！\n");
                return 0;
        }

        if( query("int", me)<40 )
        {
                tell_object(me, "你演练完毕，只感思绪紊乱，看来依你的悟性，无"
                                "法将其合一。\n");
                return 0;
        }
        if( query("con", me)<40 )
        {
                tell_object(me, "你演练完毕，只觉全身真气乱窜，眼冒金星，两耳轰鸣，好"
                                "不容易才控制下来。\n");
                return 0;
        }
        if( query("str", me)<40 )
        {
                tell_object(me, "你演练完毕，只觉双臂酸疼，全身发软。\n");
                return 0;
        }
        
        if( query("dex", me)<40 )
        {
                tell_object(me, "你演练完毕，发现依你的身法暂时还无法将其融会贯通。\n");
                return 0;
        }

        if (random(100) != 1 && ! wizardp(me))
        {
                tell_object(me, "你觉得有所感悟，或许再演练一次就能融会贯通，练成六道轮回剑。\n");
                return 0;
        }

        if (me->query_skill("sword", 1) < 700)
        {
                tell_object(me, "你基本剑法火候不足，难以演练成六道轮回剑。\n");
                return 0;
        }
        if (me->query_skill("force", 1) < 700)
        {
                tell_object(me, "你基本内功火候不足，难以演练成六道轮回剑。\n");
                return 0;                
        }
        if (me->query_skill("martial-cognize", 1) < 700)        
        {
                tell_object(me, "你武学修养火候不足，难以演练成六道轮回剑。\n");
                return 0;                
        }
        if (me->query_skill("dodge", 1) < 700)        
        {
                tell_object(me, "你基本轻功火候不足，难以演练成六道轮回剑。\n");
                return 0;                
        }        
        if ((int)me->query_skill("buddhism", 1) < 200)
        {
                tell_object(me, "你禅宗心法修为不足，难以演练成六道轮回剑。\n");
                return 0;        
        }
        /*
        // 消耗轮回点
        if( query("scborn/cur_lunhui_point", me)<6 && !query("thborn/ok", me) )
        {
                tell_object(me, "你轮回点不足，无法演练成六道轮回剑。\n");
                return 0;
        }
        if( !query("thborn/ok", me) )
                addn("scborn/cur_lunhui_point", -6, me);
        */
        me->save();

        tell_object(me, HIW "一阵凡尘往事涌上心头，你几欲放声长叹。霎那间，你放眼回首，竟有一股莫名\n"
                        "的悲哀。宗师泰斗那种高出不胜寒、登泰山而小天下之感犹然而生，你只觉得以\n往的"
                        "武学现在看来是多么的渺小可笑。\n" NOR);

        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name() + "演练出"HIY"六道轮回剑"HIM"。\n");
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_learn(object me)
{

        // 与12T冲突
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me) < 4 )
                return notify_fail("你感觉体内的阴阳九转真气跌宕起伏，似乎容纳这种内功。\n");
                
        if( query("str", me)<40 )
                return notify_fail("你先天臂力不足。\n");

        if( query("int", me)<40 )
                return notify_fail("你先天悟性不足。\n");

        if( query("dex", me)<40 )
                return notify_fail("你先天身法不足。\n");
                
        if( query("con", me)<40 )
                return notify_fail("你先天根骨不足。\n");                        
                
        if( query("max_neili", me)<8000 )
                return notify_fail("你的内力修为不够，难以修炼六道轮回剑。\n");

        if ((int)me->query_skill("force", 1) < 700)
                return notify_fail("你的内功火候太浅，难以修炼六道轮回剑。\n");

        if ((int)me->query_skill("sword", 1) < 700)
                return notify_fail("你的剑法根基不足，难以修炼六道轮回剑。\n");

        if ((int)me->query_skill("dodge", 1) < 700)
                return notify_fail("你的轻功根基不足，难以修炼六道轮回剑。\n");
    
        if ((int)me->query_skill("martial-cognize", 1) < 700)
                return notify_fail("你的武学修养不足，难以修炼六道轮回剑。\n");
                    
        if ((int)me->query_skill("buddhism", 1) < 200)
                return notify_fail("你的禅宗心法修为不足，难以修炼六道轮回剑。\n");
                                            
        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的六道轮回剑。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的六道轮回剑。\n");
                
        if ((int)me->query_skill("martial-cognize", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("你的武学修养水平有限，无法领会更高深的六道轮回剑。\n");                

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("你的基本轻功水平有限，无法领会更高深的六道轮回剑。\n"); 

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("你的基本内功水平有限，无法领会更高深的六道轮回剑。\n"); 
                                                
        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("你的基本招架水平有限，无法领会更高深的六道轮回剑。\n"); 
                                                                
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
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        return notify_fail("六道轮回剑博大精深，无法简单的通过练习进步。\n");
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("lunhui-sword", 1);
        if (lvl < 200) return 70;
        if (lvl < 250) return 80;
        if (lvl < 350) return 120;
        return 150;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("lunhui-sword", 1);
        if (lvl < 200) return 200;
        if (lvl < 250) return 300;
        if (lvl < 350) return 400;
        return 500;
}


mixed hit_ob(object me, object victim, int damage_bonus)
{

        string *desc;
        object weapon;
        
        weapon=query_temp("weapon", me);
        
        if (! objectp(weapon))return damage_bonus;
        
        desc = ({
                HIY "$N" HIY "微笑一声，轻描淡写间手中" + weapon->name() + HIY "犹如一道闪电般射向$n" HIY "。\n" NOR,
                HIG "$N" HIG "运起六道真气，以气御剑，道道剑光化做雨点般地将$n" HIG "笼罩。\n" NOR,
                HIR "$N" HIR "祭起手中" + weapon->name() + HIR "，煞时天云突变，狂风袭来，$n" HIR "只觉心中有说不出的难受。\n" NOR,
        });
        
        if (me->is_busy() 
           || random(4) >= 1
           || ! living(victim) 
           || damage_bonus < 120 
           || query("neili", me)<500
           || me->query_skill("lunhui-sword", 1) < 700) 
                return 0; 

        // 追加特效
        victim->receive_wound("qi", damage_bonus * 2, me);
        // 1200级后再追加50%伤害
        if (me->query_skill("lunhui-sword", 1) >= 1200)
                victim->receive_wound("qi", damage_bonus / 2, me);
        
        if (random(3) == 1)victim->start_busy(3 + random(3));
        
        if( random(10) == 1)addn("neili", -1*me->query_skill("lunhui-sword",1)*2, victim);
        
        return desc[random(sizeof(desc))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp, cost;

        if ((int)me->query_skill("lunhui-sword", 1) < 350
           || me->query_skill_mapped("parry") != "lunhui-sword"
           || query("neili", me)<200
           || ! living(me))
                return;

        
        cost = damage / 2;
        if (cost > 100) cost = 100;

        ap = ob->query_skill("force", 1) * 4 + ob->query_skill("martial-cognize", 1);
        dp = me->query_skill("lunhui-sword", 1) * 6 + me->query_skill("martial-cognize", 1);

        if( query("reborn/times", ob) < 4 )dp+=1000;
        
        if (dp + random(dp / 2) >= ap)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIW "微微一笑，竟化做一道剑光，消失了。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM "$n" HIW "御剑如风，不退反进，竟将$N" HIW "这招化解。\n" NOR]);
                        break;
                default:
                        result += (["msg" : MAG "$n" HIW "轻舞数剑，身前数股旋风将其围住，令任何招式都无从攻击。\n" NOR]);
                        break;
                }
                return result;
        }
}
string perform_action_file(string action)
{
        return __DIR__"lunhui-sword/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"lunhui-sword/exert/" + action;
}

int difficult_level()
{
        return 25000;
}

void skill_improved(object me)  
{ 
        int lvl;
        
        lvl = me->query_skill("lunhui-sword", 1); 

        if( lvl >= 500 && 
            !query("can_perform/lunhui-sword/xiuluo", me) )  
        { 
                tell_object(me, HIC "你通晓了轮回剑「" HIR "修罗剑神" HIC "」的奥秘。\n" NOR);     
                set("can_perform/lunhui-sword/xiuluo", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 600 && 
            !query("can_perform/lunhui-sword/lan", me) )  
        { 
                tell_object(me, HIC "你通晓了轮回剑「" HIR "兰剑舞" HIC "」的奥秘。\n" NOR);     
                set("can_perform/lunhui-sword/lan", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        }
}
