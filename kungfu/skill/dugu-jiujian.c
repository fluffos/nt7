// This program is a part of NITAN MudLIB
// dugu-jiujian.c 独孤九剑

#include <ansi.h>
#include <combat.h>

inherit SKILL;

string *parry_msg = ({ 
        "却见$n踏前一步，剑式斜指你的右臂，想要使$P闪身而退。\n", 
        "$n以攻为守，以进为退，凝神运气向$P猛攻快打地挥出方位大异的泰山「快活三」三剑。\n", 
        "$n剑法突变，剑势伸缩不定，奔腾矫夭，逆使嵩山剑法的「天外玉龙」企图迫使$P变招。\n", 
        "$n突然一剑点向$P的$l，虽一剑却暗藏无数后着，$P手足无措，攻势不由自主停了下来。\n" 
        "$n不闪不避，举剑闪电般使出「叠翠浮青」反削$P的$l，想挡过你此招。\n", 
        "$n突然使出青城派松风剑法的「鸿飞冥冥」，长剑对着$P一绞，企图突破$P的攻势。\n" 
        "$n挺剑一招象是「白云出岫」回刺$P的$l，企图将$P的攻势化解。\n", 
        "只见$n不退反进，身如飘风，一式「天柱云气」动向无定，挡住了$P的\n进攻。\n", 
        "$n不退反进，使出恒山剑招「绵里藏针」，森森剑气充溢四周！架开了$P的这招\n", 
}); 

mapping *action = ({
([      "action": HIW "但见$N挺身而上，$w" + HIW "一旋，一招仿佛泰山剑法的「来鹤清泉」直刺$n的$l" NOR,
        "attack": 70,
        "dodge" : 60,
        "parry" : 70,
        "damage": 120,
        "lvl" : 0,
        "damage_type" : "刺伤"
]),
([      "action": YEL "$N奇诡地向$n挥出「泉鸣芙蓉」、「鹤翔紫盖」、「石廪书声」、「天柱云气」及「雁回祝融」衡山五神剑" NOR,
        "attack": 71,
        "parry" : 72,
        "dodge" : 60,
        "damage": 120,
        "lvl" : 10,
        "damage_type" : "刺伤"
]),
([
        "action": GRN "$N剑随身转，续而刺出十九剑，竟然是华山「玉女十九剑」，\n但奇的是这十九剑便如一招，手法之快，直是匪夷所思" NOR,
        "attack": 72,
        "dodge" : 64,
        "parry" : 78,
        "damage": 150,
        "lvl" : 20,
        "damage_type" : "刺伤"
]),
([      "action": BLU "$N剑势忽缓而不疏，剑意有余而不尽，化恒山剑法为一剑，向$n慢慢推去" NOR,
        "parry" : 73,
        "attack": 73,
        "dodge" : 65,
        "damage": 125,
        "lvl" : 30,
        "damage_type" : "刺伤"
]),
([      "action": HIR "$N剑意突焕气象森严，便似千军万马奔驰而来，长枪大戟，黄沙千里，尽括嵩山剑势击向$n的$l" NOR,
        "parry" : 74,
        "attack": 74,
        "dodge" : 68,
        "damage": 130,
        "lvl" : 40,
        "damage_type" : "刺伤"
]),
([      "action": CYN "却见$N身随剑走，左边一拐，右边一弯，剑招也是越转越加狠辣，竟化「泰山十八盘」为一剑攻向$n" NOR,
        "attack": 75,
        "parry" : 75,
        "dodge" : 60,
        "damage": 120,
        "lvl" : 50,
        "damage_type" : "刺伤"
]),
([      "action": HIY "$N剑招突变，使出衡山的「一剑落九雁」，削向$n的$l" + HIY "，\n怎知剑到中途，突然转向，大出$n意料之外" NOR,
        "attack": 76,
        "parry" : 76,
        "dodge" : 64,
        "damage": 120,
        "lvl" : 60,
        "damage_type" : "刺伤"
]),
([      "action": MAG "$N吐气开声，一招似是「独劈华山」，手中$w" + MAG "向下斩落，直劈向$n的$l" NOR,
        "attack": 77,
        "dodge" : 67,
        "parry" : 77,
        "damage": 140,
        "lvl" : 70,
        "damage_type" : "刺伤"
]),
([      "action": HIB "$N手中$w" + HIB "越转越快，使的居然是衡山的「百变千幻云雾十三式」，\n剑式有如云卷雾涌，旁观者不由得目为之眩" NOR,
        "attack": 78,
        "dodge" : 60,
        "parry" : 78,
        "damage": 140,
        "lvl" : 80,
        "damage_type" : "刺伤"
]),
([      "action": HIM "$N满场游走，东刺一剑，西刺一剑，令$n莫明其妙，分不出$N剑法的虚实" NOR,
        "attack": 79,
        "dodge" : 65,
        "parry" : 79,
        "damage": 160,
        "lvl" : 90,
        "damage_type" : "刺伤"
]),
([      "action": HIC "$N抱剑旋身，转到$n身后，杂乱无章地向$n刺出一剑，不知使的是什么剑法" NOR,
        "attack": 80,
        "parry" : 80,
        "dodge" : 65,
        "damage": 160,
        "lvl" : 100,
        "damage_type" : "刺伤"
]),
([      "action": HIW "$N突然一剑点向$n的$l，虽一剑却暗藏无数后着，$n手足无措，不知如何是好" NOR,
        "attack": 81,
        "parry" : 81,
        "dodge" : 66,
        "damage": 170,
        "lvl" : 110,
        "damage_type" : "刺伤"
]),
([      "action": RED "$N剑挟刀势，大开大阖地乱砍一通，但招招皆击在$n攻势的破绽，迫得$n不得不守" NOR,
        "attack": 82,
        "dodge" : 71,
        "parry" : 82,
        "damage": 175,
        "lvl" : 120,
        "damage_type" : "刺伤"
]),
([      "action": YEL "$N反手横剑刺向$n的$l，这似有招似无招的一剑，威力竟然奇大，$n难以看清剑招来势" NOR,
        "attack": 83,
        "dodge" : 70,
        "parry" : 83,
        "damage": 180,
        "lvl" : 130,
        "damage_type" : "刺伤"
]),
([      "action": HIR "$N举剑狂挥，迅速无比地点向$n的$l，却令人看不出其所用是什么招式" NOR,
        "attack": 84,
        "parry" : 84,
        "dodge" : 60,
        "damage": 170,
        "lvl" : 140,
        "damage_type" : "刺伤"
]),
([      "action": HIM "$N随手一剑指向$n，落点正是$n的破绽所在，端的是神妙无伦，不可思议" NOR,
        "attack": 85,
        "parry" : 85,
        "dodge" : 64,
        "damage": 180,
        "lvl" : 150,
        "damage_type" : "刺伤"
]),
([      "action": CYN "$N脸上突现笑容，似乎已看破$n的武功招式，胸有成竹地一剑刺向$n的$l" NOR,
        "attack": 86,
        "dodge" : 60,
        "parry" : 86,
        "damage": 180,
        "lvl" : 160,
        "damage_type" : "刺伤"
]),
([
        "action": RED "$N将$w"+ RED "随手一摆，但见$n自己向$w"+ RED "撞将上来，神剑之威，实人所难测" NOR,
        "attack": 90,
        "dodge" : 70,
        "parry" : 90,
        "damage": 200,
        "lvl" : 170,
        "damage_type" : "刺伤"
])
});

mapping *action2 = ({ 
([      "action" : HIW "但见$N手中$w破空长吟，平平一剑刺向$n，毫无招式可言" NOR, 
        "force" : 300,
        "attack": 120, 
        "dodge" : 120, 
        "parry" : 120, 
        "damage": 180, 
        "damage_type" : "刺伤" 
]), 
([      "action" : HIW "$N揉身欺近，轻描淡写间随意刺出一剑，简单之极，无招无式" NOR,
        "force" : 300, 
        "attack": 130, 
        "dodge" : 130, 
        "parry" : 130, 
        "damage": 190, 
        "damage_type" : "刺伤" 
]), 
([      "action" : HIW "$N身法飘逸，神态怡然，剑意藏于胸中，手中$w随意挥洒而出，独孤" 
                       "九剑已到了收发自如的境界" NOR, 
        "force" : 300,
        "attack": 140, 
        "dodge" : 140, 
        "parry" : 140, 
        "damage": 200, 
        "damage_type" : "刺伤" 
]), 
}); 

int double_attack() { return 1; }

int valid_enable(string usage) 
{ 
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me) 
{ 
        object ob; 
        
        if( !(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "sword" )
                return notify_fail("你必须先找一把剑才能练剑法。\n"); 
        
        if( query("int", me)<34 )
                return notify_fail("你的天资不足，无法理解独孤九剑的剑意。\n"); 
        
        // if (me->query("dugu-jiujian/nothing") && 
        if (
            query("con", me)<26 )
                return notify_fail("你先天根骨不足，无法理解独孤九剑的剑意。\n"); 
            
        if( query("character", me) == "心狠手辣" )
                return notify_fail("你一心想杀尽敌人，没能理解独孤九剑的的真正含义。\n"); 
        
        if( query("character", me) == "阴险奸诈" )
                return notify_fail("你一心想怎么学好剑法去害人，结果没能理解独孤九剑。\n"); 
        
        if( query("character", me) == "光明磊落" )
                return notify_fail("你心中暗道：什么独孤九剑，乱七八糟的，没有半点气势。\n"); 
        
        if (me->query_skill("sword", 1) < 100) 
                return notify_fail("你的基本剑法造诣太浅，无法理解独孤九剑。\n"); 
        
        if (me->query_skill("sword", 1) < me->query_skill("dugu-jiujian", 1)) 
        return notify_fail("你的基本剑法造诣有限，无法理解更高深的独孤九剑。\n"); 
        
        return 1; 
} 

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("dugu-jiujian", 1);
        
        if( query("dugu-jiujian/nothing", me) )
                return action2[random(sizeof(action2))];       
                  
        if( objectp(weapon) && query("id", weapon) == "xuantiejian" )
        {
                if (me->query_str() >= 60 && me->query_int() >= 36 
                &&  random(level) > 120 
                 && me->query_skill("force")>150 && query("neili", me)>400 )
                {
                        addn("neili", -100, me);
                        return ([
                                "action": HIR "$N脸色凝重虔诚，缓缓举起玄铁重剑，突然跃起身剑合一，"
                                          "驭剑化为一道黑气向$n冲刺而去" NOR,
                                "damage": 400,
                                "attack": 100,
                                "dodge" : 80,
                                "parry" : 80,
                                "damage_type" : "刺伤"
                        ]);
                }
        }
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        return notify_fail("独孤九剑只能通过「"+RED+"总诀式"+NOR+"」来演练。\n");
}

string perform_action_file(string action)
{
        return __DIR__"dugu-jiujian/" + action;
}

int query_effect_parry(object attacker, object me) 
{ 
        object weapon; 
        int lvl; 
        
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return 0; 
        
        lvl = me->query_skill("dugu-jiujian", 1); 
        if (lvl < 90)  return 0; 
        if (lvl < 100) return 50; 
        if (lvl < 125) return 55; 
        if (lvl < 150) return 60; 
        if (lvl < 175) return 65; 
        if (lvl < 200) return 70; 
        if (lvl < 225) return 75; 
        if (lvl < 250) return 80; 
        if (lvl < 275) return 90; 
        if (lvl < 325) return 100; 
        if (lvl < 350) return 110; 
        return 120; 
} 

void skill_improved(object me) 
{ 
        int lvl, i; 
        
        i=query("int", me)/3;
        lvl = me->query_skill("dugu-jiujian", 1); 
        
        if (lvl > 120 
         && query("can_perform/dugu/qi", me) <= 100 )
        { 
                if( me->add("can_perform/dugu/qi",random(i))<100 )
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
         && query("can_perform/dugu/po", me) <= 100 )
        { 
                if( me->add("can_perform/dugu/po",random(i))<100 )
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
         && query("can_perform/dugu/yi", me) <= 100 )
        { 
                if( me->add("can_perform/dugu/yi",random(i))<100 )
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
} 
        
int difficult_level() 
{ 
        object me = this_object(); 
        
        if( query("dugu-jiujian/nothing", me) )
                return 300; 
        
        else   return 200; 
} 
  
mixed valid_damage(object ob, object me, int damage, object weapon) 
{ 
        mixed result; 
        int ap, dp, mp; 
        object m_weapon; 
        
        if ((int) me->query_skill("dugu-jiujian", 1) < 120 
         || !(m_weapon=query_temp("weapon", me) )
        ||  ! living(me) 
         || query("skill_type", m_weapon) != "sword" )
                return; 
        
        mp = ob->query_skill("count", 1); 
        ap = ob->query_skill("parry") + mp; 
        dp = me->query_skill("parry", 1) / 2 + 
        me->query_skill("dugu-jiujian", 1); 
          
        // 无招 
        if( query("dugu-jiujian/nothing", me) )
        { 
                if (me->query_skill("sword") * 2 / 3 + random(me->query_skill("sword")) >
                    ob->query_skill("parry")) 
                { 
                        result = ([ "damage": -damage ]); 
        
                        result += (["msg" : HIC "$n" HIC "突然举剑一刺，剑招随意无章，"
                                            "却莫明奇妙地突破了$N的攻势，大出$N意料。\n"
                                            "$n一转剑势，剑招源源而出，对$N发动攻势！\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
        
                        if (! ob->is_busy())
                        ob->start_busy(1 + random(2)); 
                        return result;
                } 
              
        } 
        
        if (ap / 2 + random(ap) < dp) 
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
} 
            
mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        mixed result;
        int lvl; 
        object weapon, weapon2; 
        int i, ap, dpp, dpd, dpf; 
        string type, msg, msg1; 
        
        lvl = me->query_skill("dugu-jiujian", 1); 
        
        if( query("neili", me)<300
        ||  me->query_skill_mapped("sword") != "dugu-jiujian" 
         || !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"
         || !query("dugu-jiujian/nothing", me) )
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
                        result = ([ "damage" : damage_bonus / 2 ]); 
                     
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
                message_vision(HIC "\n$N" HIC "随意挥洒手中的" + weapon->name() + 
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
                    !query_temp("dugu-jiujian/lian", me) )
                { 
                        weapon=query_temp("weapon", me);
                        message_sort(HIY "\n$N" HIY "胸藏剑意，手中" + weapon->name() + HIY  
                                     "随意挥洒而出，速度之快，方位之准，显是独孤九剑已达到" 
                                     "收发自如的境界。\n" NOR, 
                                     me, victim); 
        
                        addn("neili", -270, me);
           
                        set_temp("dugu-jiujian/lian", 1, me);
                        for (i = 0; i < 5; i++) 
                        { 
                                if (! me->is_fighting(victim)) 
                                        break; 
                  
                                if (! victim->is_busy() && random(2) == 1) 
                                        victim->start_busy(1); 
        
                                COMBAT_D->do_attack(me, victim, weapon, 0); 
                        } 
                        delete_temp("dugu-jiujian/lian", me);
            
                } 
                break;                         
        } 
} 