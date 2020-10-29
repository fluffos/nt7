// Code of ShenZhou
// renshen-guo.c 人参果

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "人参果" NOR, ({"renshen guo", "guo"}));
        set_weight(90);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "枚");
                set("long", "这是一枚人参果，看上去就像一个白白胖胖的小娃娃。\n");
                set("value", 20000);
                set("no_sell", 1);
                set("medicine", 1);
        }

        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("cool_drug") > 0){
        addn("max_neili", -1, me);
        message_vision(HIR "$N吃下一枚人参果，只觉得头重脚轻，摇摇欲倒，
原来服食太急太多，药效适得其反！\n" NOR, me);
        destruct(this_object());
        return 1;
        }
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("jingli",query("max_jingli",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        if (random(2)==1) addn("max_neili", 2, me);
        set("neili",query("max_neili",  me), me);
        set("food", me->max_food_capacity(), me);
        set("water", me->max_water_capacity(), me);
        
        message_vision(HIG "$N吃下一枚人参果，只觉得精神健旺，气血充盈，体内真力源源滋生，将疲乏饥渴一扫而空! \n" NOR, me);
        me->apply_condition("cool_drug", 30);
        destruct(this_object());
        return 1;
}