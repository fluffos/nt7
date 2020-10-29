// cuixin-strike.c 摧心掌

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
int is_pbsk() { return 1; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N身形微晃，一招"CYN"「风催冰寒」"NOR"，掌挟冷风，推向$n的心房",
        "lvl"   : 0,
        "skill_name" : "风催冰寒",
]),
([        "action" : "$N出手如风，双掌微微抖动，一招"BLU"「慑影寒心」"NOR"推向$n的胸腹",
        "lvl"   : 20,
        "skill_name" : "慑影寒心",
]),
([        "action" : "$N双掌忽隐忽现，一招"HIW"「漫天雪舞」"NOR"，鬼魅般地扫向$n的肩头",
        "lvl"   : 40,
        "skill_name" : "漫天雪舞",
]),
([        "action" : "$N左掌当胸画弧，右掌疾出，一招"GRN"「飞荧罩影」"NOR"，猛地拍向$n的额头",
        "lvl"   : 60,
        "skill_name" : "飞荧罩影",
]),
([        "action" : "$N使一招"HIC"「寒川岁尽」"NOR"，双掌齐出，激起漫天的劲风，撞向$n",
        "lvl"   : 80,
        "skill_name" : "寒川岁尽",
]),
([        "action" : "$N面无表情，双臂忽左忽右地疾挥，使出"HIM"「雪原冰凌」"NOR"，十股掌气忽伸忽缩，迅猛无比地袭向$n全身各处大穴",
        "lvl"   : 100,
        "skill_name" : "雪原冰凌",
]),
([        "action" : "$N使出"RED"「旋风蔽日」"NOR"，蓦然游身而上，绕着$n疾转数圈，$n正眼花缭乱间，$N已悄然停在$n身后，右手划出一道光圈，接着右手冲出光圈猛拍$n的后背",
        "lvl"   : 120,
        "skill_name" : "旋风蔽日",
]),
([        "action" : "$N突然双手平举，$n一呆，正在猜测间，便见$N嗖的一下将双手收回胸前，接着一招"HIG"「回首银川」"NOR"，双掌如电，直拍向$n的腰间",
        "lvl"   : 140,
        "skill_name" : "回首银川",
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry" ; }
int valid_combine(string combo) { return combo=="jiuyin-baiguzhao" || combo=="dafumo-quan"; }

int valid_learn(object me)
{

        /*
        if ((int)me->query_skill("jiuyin-shengong", 1))
                return notify_fail("你已将九阴真经上的武功全部融会贯通，不必再分开学习了。\n");
        */

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
            return notify_fail("练催心掌必须空手。\n");

        if ((int)me->query_skill("force") < 100)
            return notify_fail("你的内功太差，无法练习催心掌。\n");

        if( query("max_neili", me)<1200 )
            return notify_fail("你的内力修为太浅，无法练习催心掌。\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("你的基本掌法有限，无法体会催心掌的要诣。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("cuixin-zhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的催心掌。\n");

        return 1;
}

int practice_skill(object me)
{
        /*
        if ((int)me->query_skill("jiuyin-shengong", 1))
                return notify_fail("你已将九阴真经上的武功全部融会贯通，不必再分开练习了。\n");
        */

        if( query("qi", me)<100 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<350 )
                return notify_fail("你的内力不够。\n");

        me->receive_damage("qi", 80);
        addn("neili", -300, me);
        return 1;
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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -45;
        int d_e2 = -25;
        int p_e1 = -5;
        int p_e2 = 25;
        int f_e1 = 200;
        int f_e2 = 310;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("cuixin-zhang", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 获得招数序号上限 */
                        break;
                }
        seq = random(seq);       /* 选择出手招数序号 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "内伤" : "瘀伤",
        ]);
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"cuixin-zhang/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("cuixin-zhang", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("cuixin_zhang",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIR "只听$n" HIR "闷哼了一声，看来是受到了催心掌掌劲的干扰！\n" NOR;
        }
}

void skill_improved(object me)   
{  
             int lvl; 
             lvl = me->query_skill("cuixin-zhang", 1);  
               if( lvl >= 80 &&  
                   !query("can_perform/cuixin-zhang/gu", me) )   
               {  
                       tell_object(me, HIC "你通晓了催心掌「" HIR "孤注一掷" HIC "」的奥秘。\n" NOR);     
                        set("can_perform/cuixin-zhang/gu", 1, me);  
                       me->improve_skill("martial-cognize", 1500000); 
                       me->improve_skill("martial-cognize", 1500000); 
                       me->improve_skill("martial-cognize", 1500000); 
               }  
             if( lvl >= 150 &&  
                 !query("can_perform/cuixin-zhang/cui", me) )   
             {  
                     tell_object(me, HIC "你通晓了催心掌「" HIR "夺命催心" HIC "」的奥秘。\n" NOR);     
                      set("can_perform/cuixin-zhang/cui", 1, me);  
                     me->improve_skill("martial-cognize", 1500000);    
                     me->improve_skill("martial-cognize", 1500000);    
                     me->improve_skill("martial-cognize", 1500000);    
             }  
     }  
int help(object me)
{
        write(HIC"\n摧心掌："NOR"\n");
        write(@HELP

    摧心掌为青城派歹毒掌法。摧毁敌方心脏。
    可与无影腿互备。

        学习要求：
                青冥玄功15级
                基本内功20级
                内力300
HELP
        );
        return 1;
}
