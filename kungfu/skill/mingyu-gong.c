// This program is a part of NITAN MudLIB
// mingyu-gong.c

#include <ansi.h>

inherit FORCE;

int is_pbsk() { return 1; }

int valid_force(string force) { return 1; }  
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("mingyu-gong", 1);
        return lvl /10 * lvl /10 * 15 * 28 / 10 / 20;
}
string *dodge_msg = ({
        "$N身形加速，电光挪移，饶是$n攻击范围既广且厉，却总能在间不容发的空隙避过",
        "$N空中快速转折，在$n每次攻击前又倏乎消失，一下子就脱出$n的攻击范围",        
        "$N只觉眼前一花，只见到$n身形一幌，自己的招数居然莫名其妙就落空了", 
        "$N凭著高速身法，在$n的攻击范围内进退趋避，险险闪过一道又一道的攻击",
        "$N腾挪快速，竟然在空中形成身影残像，有如无数$N一起挪动",
        "$n眼前忽然一花，眼前$N的身影似乎有些淡化，而另外一个$N竟尔出现在面前不足一尺的近处",
});

string *parry_msg = ({
        "眼看$n转眼已攻至，$N轻描淡写，却又快绝无比，把$n的招式化于无形",
        "$n眼看得手之际，突觉一股阴柔劲道蚀$W急上，没等接触，整条手臂已剧痛起来，忙叫一声不好，慌然急退",
        "$n陡觉手上劲力如泥牛入海，摸不着底处，暗叫不妙，$N却又已经攻至",
        "$n心下一凛，但见对手守势，如万里长空，旷远不知其深，包容万物，无从下手",
});


string *action_msg = ({
        "$N十指微张，看似简单的，却在张开的同时，爆发了沛然莫敌的冲击力击向$n",
        "$N运起明玉功，身体逐渐变得透明，森寒杀意如有实质，隔空锁镇住$n",
        "$N双手一张一收，平实的一招却让$n有如处于漩涡之中，动弹不得",
        "$N将明玉功提至极限，一招一式，神妙无方，如天外神龙，纵横来去",
        "$N手中$w幻化出点点星雨，迳自往四面八方洒去，形成无数小气旋",
        "$n陡觉一股气旋急压而下，扯得自己身形不定，同时一股阴柔内劲夹於其，尽数封死了$n周遭退路",
        "$N一招击中$n，同时一股阴柔内劲绵绵不绝的涌入$n的体内，侵筋蚀脉",
        "$N催运明玉功，，进似神龙矫捷，退若灵蛇窜动，$n只觉得眼花撩乱",
        "$N微一扬手，绕身明玉劲如毒蛇洪水似地爆起，群蛇乱舞，乱攻向$n",
        "$n只觉得股阴柔内劲传来，跟著便是手上一沉，好似有什么东西，让手臂变成千斤重物，拖的自己直往前跌",
});

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 500 + random(120),
                "attack": 200 + random(60),
                "dodge" : -80 - random(60),
                "parry" : -80 - random(60),
                "damage" : 180 + random(60),
                "damage_type" : random(2)?"刺伤":"内伤",  
        ]);
}

string query_dodge_msg(string limb){        return dodge_msg[random(sizeof(dodge_msg))];}

string query_parry_msg(object weapon){        return parry_msg[random(sizeof(parry_msg))];}

int valid_enable(string usage)
{
         return usage == "force" || usage == "unarmed" || usage == "sword" ||
                usage == "dodge" || usage == "parry";
}

int double_attack() { return 1; }

int valid_learn(object me)
{
        int level;
        int i;

        if( query("gender", me) != "女性" )
                return notify_fail("你纯阴之气不足，难以领会高深的明玉功。\n");
                
        if( query("sex/times", me) )
                return notify_fail("修炼明玉功必须是处子之身。\n");

        if( query("int", me)<30 )
                return notify_fail("你觉得明玉功过于艰深，难以理解。\n");

        if( query("max_neili", me)<3500 )
            return notify_fail("你的内力修为太浅，无法运转明玉功。\n");

        level = me->query_skill("mingyu-gong", 1);

        if ((int)me->query_skill("martial-cognize", 1) < 100)
                return notify_fail("你觉得明玉功过于深奥，以自己的武学修养"
                                   "全然无法明白。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的基本内功修为不足，难以运转明玉功。\n");

        if (me->query_skill("force", 1) < level)
                return notify_fail("你对基本内功的理解还不够，无法继续领会更"
                                   "高深的明玉功。\n");

        if (me->query_skill("unarmed", 1) < level)
                return notify_fail("你对基本拳脚的理解还不够，无法继续领会更"
                                   "高深的明玉功。\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;

        if ((int)me->query_skill("mingyu-gong", 1) < 150
           || me->query_skill_mapped("parry") != "mingyu-gong"
           || me->query_skill_mapped("force") != "mingyu-gong"
           || me->query_skill_mapped("unarmed") != "mingyu-gong"
            || query("neili", me)<500
           || ! living(me))
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        ap = ob->query_skill("force") * 12 + ob->query_skill("count", 1) * 6;
        dp = me->query_skill("force") * 12;

        if (ap / 2 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "默念明玉功总诀，收敛"
                                            "内劲，承下$N" + HIR "这一招，$N" HIR
                                            "只觉犹如进入绵绵长河中，丝毫不起作用。\n"
                                            NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "一招击中$n" HIR "上身"
                                            "，可却犹如击在棉花上一般，力道顿时"
                                            "消失得无影无踪。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "但见$n" HIR "微微一笑，浑若无事"
                                            "的接下了$N" HIR "这一招，纯阴之劲随之而起，"
                                            "没有受到半点伤害。\n" NOR]);
                        break;
                }
                return result;
        }
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int i;
        object weapon;

        lvl = me->query_skill("mingyu-gong", 1);
        weapon=query_temp("weapon", me);

        // 配合pfm qiong
        if( query_temp("mingyu_pfm/qiong", me )
              && !query_temp("mingyu_pfm/qiong_hit_done", me )
             && living(victim)
             && !me->is_busy()
             && !weapon)
        {
                addn("neili", -40, me);
                message_vision(HIY"\n$N前招将落，后招已至，前后两招形如一式，此起彼伏，连绵不绝！\n"NOR,me);
                set_temp("mingyu_pfm/qiong_hit_done", 1, me);
                COMBAT_D->do_attack(me,victim,0,3);
                COMBAT_D->do_attack(me,victim,0,3);
                COMBAT_D->do_attack(me,victim,0,3);
                COMBAT_D->do_attack(me,victim,0,3);
                delete_temp("mingyu_pfm/qiong_hit_done", me);
                me->start_busy(1);
                return 1;
        }


        if (damage_bonus < 100
           || lvl < 150
            || query("neili", me)<300
           || me->query_skill_mapped("force") != "mingyu-gong"
           || me->query_skill_mapped("unarmed") != "mingyu-gong"
           || me->query_skill_prepared("unarmed") != "mingyu-gong")
                return 0;
        // if (damage_bonus / 2 > victim->query_con())
        if (damage_bonus > victim->query_con()/10)
        {
                addn("neili", -50, me);
                victim->receive_wound("qi", (damage_bonus - 80) / 2, me);
                return random(2) ? HIR "只见$N" HIR "明玉功内劲自体内迸发，一股柔劲随招式"
                                   "而荡漾，摧毁了$n" HIR "的真元！\n" NOR:

                                   HIR "$N" HIR "明玉功的潜力发挥了出来，突然间$n"
                                   HIR "只感喉咙一甜，喷出一口鲜血！\n" NOR;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("mingyu-gong", 1);
        if (lvl < 150) return 0;
        if (lvl < 200) return 70;
        if (lvl < 250) return 80;
        if (lvl < 300) return 90;
        if (lvl < 350) return 100;
        if (lvl < 400) return 110;
        return 120;
}

int practice_skill(object me)
{
        return notify_fail("明玉功只能用学(learn)的来增加熟练度。\n");
}

int difficult_level()
{
        return 1000;
}

string perform_action_file(string action)
{
        return __DIR__"mingyu-gong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"mingyu-gong/exert/" + action;
}

void skill_improved(object me)
{
        int lvl, layer;

        lvl = me->query_skill("mingyu-gong", 1);
        layer = lvl / 40;

        if ((lvl % 40) == 0 && layer > 9)
        {
                tell_object(me, HIY "你的明玉功又进了一层。\n" NOR);
        } else
        if ((lvl % 40) == 0)
        {
                tell_object(me, HIY "你炼成了第" + chinese_number(layer) +
                                "层的明玉功。\n" NOR);
        }

        if( lvl > 200 &&
            !query("can_perform/mingyu-gong/qiong", me) ) 
        {
                tell_object(me, HIC "你通晓了明玉功「" HIR "琼楼玉宇" HIC "」的奥秘。\n" NOR);    
                set("can_perform/mingyu-gong/qiong", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
        }

        if( lvl > 300 &&
            !query("can_perform/mingyu-gong/gua", me) ) 
        {
                tell_object(me, HIC "你通晓了明玉功「" HIR "冰河倒挂" HIC "」的奥秘。\n" NOR);    
                set("can_perform/mingyu-gong/gua", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
        }

        if( lvl > 500 &&
            !query("can_perform/mingyu-gong/moqi", me) ) 
        {
                tell_object(me, HIC "你通晓了明玉功「" HIR "魔气血杀" HIC "」的奥秘。\n" NOR);    
                set("can_perform/mingyu-gong/moqi", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
        }
}
