// xuelian.c 雪莲
// Modified by Dumbness, 2003-5-21 20:39

#include <ansi.h>;
#include <armor.h>

inherit HEAD;

void init();

void create()
{
        set_name(HIM"雪莲"NOR, ({"xuelian", "lian", "lotus"}));
        set_weight(90);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "朵");
                set("long", HIW"这是一朵晶莹的雪莲，她傲然于银白色的雪山之巅绽放，清澈灵动，如清风\n般抚慰你的心田。\n"NOR);
                set("value", 20000);
                set("no_sell", 1);
                set("no_put",1);
                set("medicine", 1);
                set("only_do_effect", 1);
                set("armor_prop/per", 5);
                set("armor_prop/per", 2); 
                set("wear_msg",         
                        HIM"$N轻轻的戴上那朵传说中的雪莲花，自己仿佛也变成了一朵傲然绽放于雪山\n"
                        "之颠的雪莲——不食人间烟火般的清澈，晶莹剔透的眼波流转，如一缕轻风\n"
                        "般的身影夜夜徘徊在情人的梦乡……\n"NOR);
                set("remove_msg", WHT"$N轻轻地把$n"WHT"从头上摘了下来，顿时黯然失色，不复婉转灵动。\n"NOR); 
        }
        setup();
}

int do_effect(object me)
{
        if (me->query_condition("cool_drug") > 0)
        {
                addn("max_jingli", -5, me);
                addn("eff_jing", -5, me);
                message_vision(HIR "$N吃下一枚雪莲，只觉得头重脚轻，摇摇欲倒，原来服食太急太多，药效适得其反！\n" NOR, me);
                destruct(this_object());
                return 1;
        }
        message_vision(HIM"$N吃下一支雪莲，一股秋菊似的幽香沁入心肺，顿觉神清气爽。\n"NOR, me);
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("jingli",query("max_jingli",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        me->apply_condition("cool_drug", 30);

        if (random(3)==1)
        { 
                if( (me->query_jingli_limit()-query("max_jingli", me))>5 )
                {
                        addn("max_jingli", 5, me);
                        addn("eff_jing", 5, me);
                }
        }

        set("neili",query("max_neili",  me), me);
        set("jingli",query("max_jingli",  me), me);
        
        if ((int)me->query_condition("snake_poison") > 0) 
                me->apply_condition("snake_poison", 0);
  
        if ((int)me->query_condition("insect_poison") > 0) 
                me->apply_condition("insect_poison", 0);
 
        if ((int)me->query_condition("sl_poison") > 0) 
                me->apply_condition("sl_poison", 0);
   
        if ((int)me->query_condition("xx_poison") > 10 
                && (int)me->query_condition("xx_poison") < 50) 
                me->apply_condition("xx_poison", 0);
        destruct(this_object());
        return 1;
}