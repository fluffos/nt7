// This program is a part of NITAN MudLIB 
// redl 2013/7
// fuyu-jian.c 覆雨剑法
/*知识技能支持  <-      心源外照，
                                        浪翻云处，进入发呆状态时才能依几率提高，
                                        意味着不能同时做其他研究练习，加大了提高的难度。
                                        变相限制了这剑法无法练到绝顶高度，只是大米技能。
                                        */
//剑法排他性，以免兼学其他强力剑法
//限制男性专属，对明玉功、越女剑等女性专属武功做制衡


#include <ansi.h>
#include <combat.h>
inherit SKILL;

string type() { return "martial"; }
string martialtype() { return "skill"; }
//int action_po(object me, object victim, object weapon, int damage);//
//int action_busy(object me, object victim, object weapon, int damage);
//int action_damage(object me, object victim, object weapon, int damage);//
//int action_parry(object me, object victim, object weapon, int damage);
//int action_dodge(object me, object victim, object weapon, int damage);

//string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

string *parry_msg = ({
        NOR"$n双手乱舞，随意化出一条潮水般的"YEL"蛟龙"NOR"，完全消去了$P攻势。\n"NOR, 
        NOR"$n略缩手臂，漫天的"HIG"烟雨"NOR"光点爆开，一时之间$P眼里满是银芒，急忙大惊退开。\n"NOR, 
        NOR"$n暴喝一声，右手挽起一串"HIY"剑花"NOR"玄妙无比，缠得$P是手忙脚乱，进退两难。\n"NOR,
        NOR"$n手里剑倏地不见，半空中一轮"HIC"明月"NOR"突显并爆射开来，如雨的剑芒挡住了$P的攻势。\n"NOR, 
});

mapping *action = ({
([      "action" : "$N手上的$w弹起点点毫光，使出「" HIB "一网情深" NOR "」剑花儿像一张网般，迎头向$n罩去。",
        "force" : 160,
        "attack": 150,
        "dodge" :-100,
        "parry" :-100,
        "damage": 120,
        "damage_type" : "刺伤",
        "lvl" : 0,
        "skill_name" : "一网情深"
]),
([      "action" : "在$N快速的飞舞下$w响出尖啸，一招「" YEL "怒蛟升海" NOR "」在空中爆出万千雨点，像狂风般卷向$n。",
        "force" : 230,
        "attack": 150,
        "dodge" :-120,
        "parry" :-100,
        "damage": 150,
        "damage_type" : "刺伤",
        "lvl" : 0,
        "skill_name" : "怒蛟升海"
]),
([      "action" : "$N似醒还醉的眼忽地睁亮，一式「" HIR "醉眼睨虹" NOR "」爆出无法形容的精芒，$w化作数道长虹速度激增，电射$n的$l。",
        "force" : 300,
        "attack": 180,
        "dodge" :-140,
        "parry" :-100,
        "damage": 180,
        "damage_type" : "刺伤",
        "lvl" : 0,
        "skill_name" : "醉眼睨虹"
]),
([      "action" : "$N手里剑芒再起，施展「" HIG "洞庭烟雨" NOR "」无数强光从$N怀里暴起，化作千万道$w围击$n。",
        "force" : 400,
        "attack": 150,
        "dodge" :-120,
        "parry" :-90,
        "damage": 300,
        "damage_type" : "刺伤",
        "lvl" : 1000,
        "skill_name" : "洞庭烟雨"
]),
([      "action" : "$N面含微笑，使出「" HIY "诗酒浣剑" NOR "」，$w挽起爆出一个个剑花扭成一串波纹，以奇怪的角度往$n刺去。",
        "force" : 280,
        "attack": 280,
        "dodge" :-140,
        "parry" :-90,
        "damage": 200,
        "damage_type" : "刺伤",
        "lvl" : 2000,
        "skill_name" : "诗酒浣剑"
]),
([      "action" : "$N手中的$w倏地不见，半空中的皎月寒光突然爆射开来正是「" HIC "明月依旧" NOR "」，闪烁的剑芒如光雨往$n的周围十丈激射而下。",
        "force" : 500,
        "attack": 260,
        "dodge" :-120,
        "parry" :-110,
        "damage": 300,
        "damage_type" : "刺伤",
        "lvl" : 3000,
        "skill_name" : "明月依旧"
]),
([      "action" : "不知何时$N瞬间已欺近$n身前三尺，简单一式「" HIM "彩云不归" NOR "」，手里的$w化为半点星芒，微微一闪直刺$n的心脏。",
        "force" : 450,
        "attack": 360,
        "dodge" :-140,
        "parry" :-110,
        "damage": 320,
        "damage_type" : "刺伤",
        "lvl" : 4000,
        "skill_name" : "彩云不归"
]),
});


int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int valid_learn(object me)
{
        object ob;
        if( !(ob=query_temp("weapon", me) )
        ||  query("skill_type", ob) != "sword" )
                return notify_fail("你必须先找一把剑才能练剑法。\n");
        if( query("str", me)<23 )
                return notify_fail("你的臂力不足，无法理解覆雨剑法。\n");
        if( query("int", me)<30 )
                return notify_fail("你的悟性不足，无法理解覆雨剑法。\n");
        if( query("con", me)<28 )
                return notify_fail("你的根骨不足，无法理解覆雨剑法。\n");
        if( query("dex", me)<26 )
                return notify_fail("你的身法不足，无法理解覆雨剑法。\n");
        if( query("character", me) == "心狠手辣" )
                return notify_fail("你天性缺乏仁慈，无法理解覆雨剑法。\n");
        if( me->query_skill("sword", 1) < me->query_skill("fuyu-jian", 1) )
                return notify_fail("你的基本剑法造诣有限，无法理解更高深的覆雨剑法。\n");
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("覆雨剑法只能用学(learn)来增加熟练度。\n");
/*        object weapon;
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
        if( query("qi", me)<2000 || query("neili", me)<800)
                return notify_fail("你的内力或气不够练覆雨剑法。\n");
        me->receive_damage("qi", 200);
        addn("neili", -80, me);
        return 1;*/
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
//      return action[random(sizeof(action))];
        int i, level;
        level = (int) me->query_skill("fuyu-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

/*
int action_damage(object me, object victim, object weapon, int damage)
{
        string msg;
        string*limbs=query("limbs", victim);
        int dam;
        int skill= me->query_skill("lonely-sword", 1);
        if( !me->is_fighting(victim) ) return 0;
        if( damage == RESULT_DODGE && !victim->is_busy()
        &&  skill > 100
        &&  objectp(weapon=query_temp("weapon", me) )
        &&  query("neili", me)>100
        &&  random(skill) > victim->query_skill("force",1)/2 ) //躲过
        {
                addn("neili", -50, me);
                message_combatd("\n$N一声长啸:"HIW"「剑旋离身，剑啸震山河」"NOR", 瞬间剑芒大作,朝$n激射而至！\n",me,victim);
                dam=skill*2+query_temp("apply/damage", me);
                dam-=query_temp("apply/armor", victim);
                if (dam < 0 ) dam = 0;
                victim->receive_damage("qi", dam);
                msg = COMBAT_D->damage_msg(dam, "刺伤"); //此次伤害
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg, me, victim);
                COMBAT_D->report_status(victim);
                return 1;
        } else 
        if( damage > 0 && !victim->is_busy()
        &&  skill > 100
        &&  query("neili", me)>100
        &&  random(skill) > victim->query_skill("force",1)/4)   //打中对方
        {
                addn("neili", -50, me);
                message_combatd("\n$N突然悟出"HIW"「练精化气, 练气化神, 练神还虚」"NOR"之真理, 手中长剑突然消失, 朝$n飞至！\n",me,victim);
                dam=skill+query_temp("apply/damage", me);
                dam-=query_temp("apply/armor", victim);
                if (dam < 0 ) dam = 0;
                victim->receive_damage("qi",dam);
                msg = COMBAT_D->damage_msg(skill*2, "刺伤"); //此次伤害
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg,me,victim);
                COMBAT_D->report_status(victim);
                return 1;
        }
        return 1;
}

int action_po(object me, object victim, object weapon, int damage)
{
        // 破对方武功、内功  为终极效果
        int skill= me->query_skill("lonely-sword", 1);
        string v_force = victim->query_skill_mapped("force");
        int jiali;
        if( !me->is_fighting(victim) ) return 0;
        if( damage > 0 )// 打中对方 破内功 或者破内力
        {
                if( v_force && skill > 250
                &&  random(skill/2) > random(victim->query_skill("force"))
                &&  random(skill) > 200
                &&  victim->query_map_skill("force")
                &&  objectp(weapon=query_temp("weapon", me) )
                &&  random(3)==1 )
                {
                        addn("neili", -100, me);
                        victim->map_skill("force");
                        message_combatd(HIC "$N一剑得手，剑招源源而出，剑尖直刺$n丹田！\n",me,victim);
                        message_combatd(RED "$n只觉混身如遭电击，真气劲力紊乱难控，已然不能施展"+to_chinese(v_force)+"！\n" NOR,me,victim);
                        return 1;
                } else 
                if( random(me->query_skill("lonely-sword",1)) > 100 &&
                    random(me->query_skill("sword",1))>100 &&
                    me->query_skill("force",1) > 120 &&  
                    !victim->is_busy() ) {
                        addn("neili", -50, me);
                        if( query("neili", victim)>600 )
                                addn("neili", -500, victim);
                        else
                                set("neili", 0, victim);
                        message_combatd(HIC "\n$N一剑得手，剑招源源而出，欲将$n团团困住！\n",me,victim);
                        message_combatd(HIM "$n急运内力，使出浑身解数，方才脱出剑圈！\n"NOR , me, victim);
                        return 1;
                }
        }
        else if( damage == RESULT_DODGE && !victim->is_busy()) //躲过  震慑对方
        {
                addn("neili", -50, me);
                message_combatd(HIY "$n只觉$N剑中暗藏无数玄机，稍一胆怯，不敢攻上前去！\n"NOR,me,victim);
                victim->start_busy(1+random(skill/50));
                return 1;
        }
        else if ( damage == RESULT_PARRY ) //对手招架住 可顺势再创对手
        {
                jiali=query("jiali", me);
                if (!jiali) jiali=10;
                if( random(skill)>140 )
                {
                        addn("neili", -50, me);
                        message_combatd(HIC "$N相交一招，已然看破$n武功套路，胸有成竹地刺出一剑!\n",me,victim);
                        victim->receive_wound("qi", (random(jiali)*2+100));
                        message_combatd(HIM"$N剑气纵横! 一道剑气划过了$n的胸口。结果鲜血狂喷!\n"NOR,me,victim);
                        COMBAT_D->report_status(victim,1);
                }
                return 1;
        }
        return 1;

}

int action_busy(object me, object victim, object weapon, int damage)
{
        int skill=me->query_skill("lonely-sword",1);
        if( !me->is_fighting(victim) ) return 0;
        if( damage <= 0 && !victim->is_busy()
        &&  skill > 100
        &&  objectp(weapon=query_temp("weapon", me) )
        &&  query("neili", me)>100
        &&  random(query("combat_exp", me))>query("combat_exp", victim)/3)//威力极小,如果没有上两个则包括躲过和招架
        {
                addn("neili", -50, me);
                message_combatd("$N顿然领悟了"HIW"「剑在神先, 绵绵不绝」"NOR"之真意, 剑尖瞬间爆出无数大大小小,\n正反斜直各种各样的圆圈, 将$n团团困住。\n",me,victim);
                victim->start_busy(2+random(skill/50));
                return 1;
        } else 
        if( damage > 0  && !victim->is_busy()
        &&  skill > 100
        &&  random(skill) > victim->query_skill("force",1)/3)
        {
                addn("neili", -30, me);
                message_combatd(CYN"$N以意驭剑，画出数个"RED"圆圈"CYN"，左右兼顾，将$n缠在正中！\n" NOR,me,victim);
                victim->start_busy(1+random(skill/50));
        }
        return 1;
}

int action_dodge(object me, object victim, object weapon, int damage)
{
        int skill=me->query_skill("lonely-sword",1);
        string msg;
        string*limbs=query("limbs", victim);
        if( !me->is_fighting(victim)) return 0;
        if( random(me->query_skill("lonely-sword",1)) >= 200 &&
            random(me->query_skill("sword",1))>180 &&
            me->query_skill("force",1) >= 200 &&
            objectp(weapon=query_temp("weapon", me)) &&
            victim->query_map_skill("dodge") ) {
                addn("neili", -50, me);
                victim->map_skill("dodge");
                if( !victim->is_busy() )
                        victim->start_busy(random(3)+1);

                msg = HIC "\n$N突然举剑一刺，剑招随便无章，却莫明奇妙地突破了$n的攻势，大出$n意料！\n" ;
                msg += HIR"$n大吃一惊，竟然忘了闪避！\n"NOR;
                message_combatd(msg,me,victim);
                return 1;
        }
        else if( damage <= 0 && random(skill) > random(victim->query_skill("dodge",1)/3))
        {
                addn("neili", -50, me);
                message_combatd("\n却见$N飘身而上，半空中举剑上挑，剑光已封住了$n身周数尺之地，攻得精巧无比！\n",me,victim);
                victim->receive_damage("qi",skill/2);
                msg = COMBAT_D->damage_msg(skill/2, "刺伤");
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg=replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg,me,victim);
                COMBAT_D->report_status(victim);
                return 1;
       }
       return 1;
}

int action_parry(object me, object victim, object weapon, int damage)
{
        int skill=me->query_skill("lonely-sword",1);
        string msg;
        string*limbs=query("limbs", victim);
        if( !me->is_fighting(victim)) return 0;
        if( damage == RESULT_DODGE &&
            random(me->query_skill("lonely-sword",1)) > 140 &&
            random(me->query_skill("sword",1))>140 &&
            me->query_skill("force",1) >= 200 &&
            objectp(weapon=query_temp("weapon", me)) &&
            victim->query_map_skill("parry") ) {
                addn("neili", -50, me);
                victim->map_skill("parry");
                if( !victim->is_busy() )
                        victim->start_busy(random(2)+1);

                msg = HIC "\n$N举剑反攻，后发先至地刺向$n，不仅把$n招术封死，更进一步发出攻击！\n" NOR;
                msg += HIY"$n难以看清剑招来势,竟然忘了招架！\n"NOR;
                message_combatd(msg,me,victim);
        }
        else if (damage <= 0 && random(skill) > random(victim->query_skill("parry",1)/3))
        {
                addn("neili", -50, me);
                msg = "\n$N一个箭步纵到$n身前，手腕微颤，挥剑斜撩，横削$n$l，剑法极尽灵动轻捷\n";
                victim->receive_damage("qi",skill/2);
                msg += COMBAT_D->damage_msg(skill/2, "刺伤"); //此次伤害
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg,me,victim);
                COMBAT_D->report_status(victim);
       }
}
*/

int double_attack() { return 1; }

int query_effect_parry(object attacker, object me)
{
        object weapon;
        int lvl;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return 0;

        lvl = me->query_skill("fuyu-jian", 1);
        if (lvl < 200)  return 20;
        if (lvl < 1000) return 50;
        if (lvl < 1500) return 60;
        if (lvl < 2000) return 70;
        if (lvl < 2500) return 80;
        if (lvl < 3000) return 100;
        if (lvl < 4000) return 120;
        return 130;
}

/*
void skill_improved(object me)
{
        int lvl, i;

        i=query("int", me)/3;
        lvl = me->query_skill("lonely-sword", 1);

        if (lvl >= 20
         && !query("can_perform/lonely-sword/jue", me))
        {
                tell_object(me, HIC "你通晓了独孤九剑「" HIW "总决式" HIC "」的奥秘。\n" NOR);
                set("can_perform/lonely-sword/jue", 1, me);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
        }

        if (lvl > 120
         && query("can_perform/lonely-sword/qi", me) <= 100 )
        {
                if( me->add("can_perform/lonely-sword/qi",random(i))<100 )
                {
                        tell_object(me, HIC "你对独孤九剑「" HIW "破气式"
                                        HIC "」有了新的领悟。\n" NOR);
                } else
                {
                        tell_object(me, HIC "你通晓了独孤九剑「" HIW "破"
                                        "气式" HIC "」的奥秘。\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }

        if (lvl > 150
         && query("can_perform/lonely-sword/po", me) <= 100 )
        {
                if( me->add("can_perform/lonely-sword/po",random(i))<100 )
                {
                        tell_object(me, HIC "你对独孤九剑「" HIR "总破式"
                                        HIC "」有了新的领悟。\n" NOR);
                } else
                {
                        tell_object(me, HIC "你通晓了独孤九剑「" HIR "总"
                                        "破式" HIC "」的奥秘。\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }

        if (lvl > 200
         && query("can_perform/lonely-sword/yi", me) <= 100 )
        {
                if( me->add("can_perform/lonely-sword/yi",random(i))<100 )
                {
                        tell_object(me, HIC "你对独孤九剑「" HIR "剑意"
                                        HIC "」有了新的领悟。\n" NOR);
                } else
                {
                        tell_object(me, HIC "你通晓了独孤九剑「" HIR "剑"
                                        "意" HIC "」的奥秘。\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }
}*/

int difficult_level()
{
        object me = this_object();
                return 180;
//        if( query("lonely-sword/nothing", me) )
//                return 300;
//        else   
//                      return 200;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, n;
        object m_weapon;

        if ((int) me->query_skill("fuyu-jian", 1) < 200
         || !(m_weapon=query_temp("weapon", me) )
        ||  ! living(me)
         || query("skill_type", m_weapon) != "sword" )
                return;

        ap = ob->query_skill("count", 1) / 2;
        ap += ob->query_skill("parry");
        ap += ob->query_skill("dodge");
        
        dp = me->query_skill("parry", 1);
        dp += me->query_skill("fuyu-jian", 1);
        
        
        if( (dp * 2 / 3 + random(dp)) > ap ) {
                result = ([ "damage": -damage ]);
                result += (["msg" : parry_msg[random(sizeof(parry_msg))]]);
                message_vision("$N垂目盯着$n的攻势，心底默数着...\n", me, ob);
                return result;
        }
        

                return result;

/*
//         // 无招
//         if( query("lonely-sword/nothing", me) )
//         {
//                 if( n = ABILITY_D->check_ability(me, "def_power-dgjj-nothing") )
//                         dp += dp * n/100;
                //if (me->query_skill("sword") * 2 / 3 + random(me->query_skill("sword")) >
                //    ob->query_skill("parry"))
                if( dp * 2 / 3 + random(dp) > ap )
                {
                        result = ([ "damage": -damage ]);

                        result += (["msg" : HIC "$n" HIC "突然举剑一刺，剑招随意无章，"
                                            "却莫明奇妙地突破了$N的攻势，大出$N意料。\n"
                                            "$n一转剑势，剑招源源而出，对$N发动攻势！\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));

                        if (! ob->is_busy())
                        ob->start_busy(2 + random(2));
                        return result;
                }
// 
//         }

        if (ap / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(6))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "突然举剑一刺，剑招随意无章，"
                                            "却莫明奇妙地突破了$N的攻势，大出$N意料。\n"
                                            "$n一转剑势，剑招源源而出，对$N发动攻势！\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        break;
                case 1:
                        result += (["msg" : HIC "$n" HIC "举剑反攻，后发先至地刺向$N，不仅把"
                                            "$N招术封死，更进一步发出攻击！\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        break;
                case 2:
                        result += (["msg" : HIC "$n" HIC "提剑回刺，落点正是$N的破绽，"
                                            "$N不得不撤招严守，身形一晃间已退出丈许！\n" NOR]);
                        break;
                case 3:
                        result += (["msg" : HIC "却见$n" HIC "踏前一步，剑式斜指$P" HIC
                                            "右臂，招式迅捷无比，使得$N" HIC "闪身而退"
                                            "。\n" NOR]);
                        break;
                case 4:
                        result += (["msg" : HIC "$n" HIC "突然一剑点向$N" HIC "，虽一剑"
                                            "却暗藏无数后着，$N" HIC "顿时手足无措，攻"
                                            "势不由自主停了下来。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "眼见避无可避，只好提剑乱刺一通，"
                                            "居然出乎意料地将$N的攻击接去。\n" NOR]);
                        break;
                }

                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "一抖手中的" + m_weapon->name() +
                                 HIY "，中攻直进一剑挺进，可是$N" HIY "反招更快"
                                 "，进袭$n" HIY "！\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "手中" + m_weapon->name() + "轻挑"
                                 "，" HIY "正指向$N" HIY "攻势中的破绽，可是$N"
                                 HIY "身形一变，破绽立刻不成为破绽。\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "手中" + m_weapon->name() + HIY
                                 "续变换数种剑招，然而$N" HIY "理也不理，再次攻"
                                 "出，丝毫不受$n" HIY "的迷惑。\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
        */
}

/*
mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed result;
        int lvl;
        object weapon, weapon2;
        int i, ap, dpp, dpd, dpf;
        string type, msg, msg1;

        lvl = me->query_skill("lonely-sword", 1);

        if( query("neili", me)<300
        ||  me->query_skill_mapped("sword") != "lonely-sword"
         || !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"
         || !query("lonely-sword/nothing", me) )
                return 0;

        ap = me->query_skill("sword");
        dpp = victim->query_skill("parry");
        dpd = victim->query_skill("dodge");
        dpf = victim->query_skill("force");

        switch(random(3))
        {
        case 1:
                if (ap * 3 / 4 + random(ap) > dpp)
                {
                        addn("neili", -100, me);
                        result = ([ "damage" : damage_bonus ]);

                        msg1 = random(2) ? HIR "$N" HIR "一剑攻出，剑气横飞，" + weapon->name() + HIR
                                           "时若游龙穿空，时若惊鸿渡云，却不知这普通的"
                                           "一剑之中竟蕴藏着如此威力。\n" NOR:
                                           HIR "$N" HIR "手中" + weapon->name() + HIR "犹"
                                           "如生了眼睛一般，一剑随意挥出，竟直刺向$n" HIR
                                           "小腹，看似平淡，但方位、力道却拿捏得恰倒好处。\n" NOR;
                        result += ([ "msg" : msg1 ]);
                        return result;
                }
                break;

        case 2:
                message_combatd(HIC "\n$N" HIC "随意挥洒手中的" + weapon->name() +
                               HIC "，招招从出其不意的方位直指$n" HIC "招式中的"
                               "破绽！\n" NOR, me, victim);

                if (! me->is_busy())
                {
                        weapon=query_temp("weapon", me);
                        weapon2=query_temp("weapon", victim);
                        if( weapon2)type=query("skill_type", weapon2);


                        if (ap * 3 / 4 + random(ap) >= dpf && weapon2
                        &&  type != "pin")
                        {
                                msg = HIW "$n" HIW "觉得眼前眼花缭乱，手中"
                                      "的" + weapon2->name() + HIW "一时竟"
                                      "然拿捏不住，脱手而出！\n" NOR;
                                weapon2->move(environment(me));
                                addn("neili", -100, me);
                        } else
                        {
                                msg = HIY "$n" HIY "略得空隙喘息，一时间却"
                                      "也无力反击。\n" NOR;
                                addn("neili", -40, me);
                        }
                }else
                if (ap * 4 / 5 + random(ap) > dpd)
                {
                        msg = HIY "$n" HIY "连忙抵挡，一时间不禁手忙脚乱，"
                              "无暇反击。\n" NOR;

                        if (! victim->is_busy())
                        victim->start_busy(1 + random(lvl / 30));
                }
                else
                {
                        msg = HIC "$N" HIC "随意挥洒着手中的" + weapon->name() +
                              HIC "刺向$n" HIC "，不过$n" HIC "防守的异常严密，$N"
                              HIC "一时竟然无法找到破绽。\n" NOR;
                        if (! victim->is_busy())
                        victim->start_busy(1);
                }
                message_combatd(msg, me, victim);
                break;

        default :
                if (ap * 2 / 3 + random(ap) > dpd &&
                    ! me->is_busy() &&
                    ! random(2) &&
                    !query_temp("lonely-sword/lian", me) )
                {
                        weapon=query_temp("weapon", me);
                        message_combatd(HIY "\n$N" HIY "胸藏剑意，手中" + weapon->name() + HIY
                                     "随意挥洒而出，速度之快，方位之准，\n显是独孤九剑已达到"
                                     "收发自如的境界。\n" NOR,
                                     me, victim);

                        addn("neili", -270, me);

                        set_temp("lonely-sword/lian", 1, me);
                        for (i = 0; i < 5; i++)
                        {
                                if (! me->is_fighting(victim))
                                        break;

                                if (! victim->is_busy() && random(2) == 1)
                                        victim->start_busy(1);

                                COMBAT_D->do_attack(me, victim, weapon, 0);
                        }
                        delete_temp("lonely-sword/lian", me);

                }
                break;
        }
}
*/

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int valid_effect(object me, object weapon, string name, int skill)
{
}
string perform_action_file(string action)
{
        return __DIR__"lonely-sword/" + action;
}

int help(object me)
{
        write(HIC"\n独孤九剑："NOR"\n");
        write(@HELP

    “独孤九剑，有进无退！”
    创制这套剑法的独孤求败前辈，名字叫做‘求败’，他毕生想
求一败而不可得，这剑法施展出来，天下无敌，当年他仗剑江湖，
无敌于天下，连找一个对手来逼得他回守一招都不可得，委实令人
可惊可佩。
    无招胜有招，敌强我更强。独孤九剑不含招式，有招既无招，
无招亦有招。独孤九剑要旨在于「悟」，不可拘泥不化，讲究料敌
机先，出奇制胜。通晓了九剑剑意，则无所施而不可。
    独孤九剑，自“总诀式”、“破剑式”、“破刀式”以至“破
枪式”、“破鞭式”、“破索式”、“破掌式”、“破箭式”而到
第九剑“破气式”。九剑的第一招“总诀式”，有种种变化，用以
体演总诀，便于修习。第二招“破剑式”，用以破解普天下各门各
派的剑法。第三招“破刀式”，用以破解单刀、双刀、柳叶刀、鬼
头刀、大砍刀、斩马刀种种刀法。第四招“破枪式”，包括破解长
枪、大戟、蛇矛、齐眉棍、狼牙棒、白蜡杆、禅杖、方便铲种种长
兵刃之法。第五招“破鞭式”，用以破解钢鞭、铁锏、点穴橛、拐
子、蛾眉刺、匕首、板斧、铁牌、八角槌、铁椎等等短兵刃，第六
招“破索式”，破解的是长索、软鞭、三节棍、链子枪、铁链、渔
网、飞锤流星等等软兵刃。第七招“破掌式”，破的是拳脚指掌上
的功夫，将长拳短打、擒拿点穴、魔爪虎爪、铁沙神掌，诸般拳脚
功夫尽数包括内在。第八招“破箭式”这个“箭”字，则总罗诸般
暗器，练这一剑时，须得先学听风辨器之术，不但要能以一柄长剑
击开敌人发射来的种种暗器，还须借力反打，以敌人射来的暗器反
射伤敌。第九剑“破气式”，是为对付身具上乘内功的敌人而用，
神而明之，存乎一心。

        学习要求：
                只能向风清扬学习
                紫霞神功100级
                内力600
HELP
        );
        return 1;
}

