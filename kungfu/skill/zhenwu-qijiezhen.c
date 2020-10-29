// zhenwu-qijiezhen.c

#include <ansi.h>

inherit SKILL;

string *action_msg = 
({
        HIR"\n$n见$N等人此去彼来，你挡我击，就如数十人般源源而上，不由得大吃一惊，\n"
            +"当下抱元守一，见招拆招，不敢再行进攻。\n\n"NOR,
        HIG"\n只见数条人影往来飞舞，有时$n突出包围，但$N等人如影随形，立即裹上。\n\n"NOR,
        HIY"\n$n见敌手越打越急，如穿花蝴蝶般乱转，有时一人作势欲踢，岂知突然往旁让\n"
            +"开，他身后一人猛然发拳打到。\n\n"NOR,
        HIB"\n$n见前面一人双手合抱，意欲肉搏，他往后面退避，后心有脚刚好踢到，凑得\n"
            "再合拍也没有。\n\n"NOR,
        HIM"\n$N一打手势，一人向右跨步，一人向左转身，阵势布开，顷刻间已将$n围在垓心。\n\n"NOR,
        HIC"\n$n一入敌围，不论如何硬闯巧闪，敌人必能以厉害招术反击，一人出手，其他四人\n"
            + "立即绵绵而上，不到敌人或死或擒，永无休止。\n\n"NOR,
        HIW"\n$n缠斗良久，不论强攻巧诱，始终脱不出包围，但对方穿梭来去，攻势凌厉，\n"
            "只得奋力抵御，毫无丝毫余暇去推敲阵法，\n\n"NOR,
});


string query_action()
{
        return action_msg[random(sizeof(action_msg))];
}

int query_limit()
{
        return 5;
}

void create()
{ 
        seteuid(getuid()); 
}

string type() 
{ 
        return "array"; 
}

int valid_learn(object me) 
{
        if( me->query_skill("force",1) < 160)
                return notify_fail("你的基本内功级别不够，无法学习五行阵。\n");
        if( me->query("combat_exp") < 800000)
                return notify_fail("你的经验，恐怕无法领悟五行阵的精髓。\n");
        return 1;
}

int practice_skill(object me)
{       
        return notify_fail("你无法通过练习来提高五行阵的修为。\n");
}

