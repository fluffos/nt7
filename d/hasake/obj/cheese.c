#include <ansi.h>

inherit ITEM;

void init()
{
       add_action("do_drink", "drink");
}


void create()
{
        set_name(HIW "乳酪" NOR, ({"cheese"}));
        set_weight(700);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "一碗香甜的鲜奶酪，不喝奶酪就不算来过大草原。\n");
                set("unit", "碗");
               set("value", 5000);
             }
}

int do_drink(string arg)
{        
        object me = this_player();
        if (!living(me)) return notify_fail("想当机吗？\n");
        if (!id(arg)) return 0;
        if( query("water", me)<me->max_water_capacity()){
        message_vision(HIG"$N骨碌骨碌地喝完一碗"+query("name", this_object())+HIG"，抹了抹嘴。\n"NOR,me);
        if( query("food", me)<me->max_food_capacity() )
           addn("food", 100, me);
        addn("water", 100, me);
               destruct(this_object());       
        return 1;
        }
}