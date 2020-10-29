// medicine: xuelian.c
// Jay 3/18/96
#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("天山雪莲", ({"xuelian", "lian", "lotus"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "支");
                set("long", "这是一支只有在寒冷的地方才能生长的雪莲。\n");
                set("value", 100);
        }
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("你要吃什么？\n");

// function of this medicine needed here
       if( query("eff_qi", this_player()) == 
           this_player(query("max_qi", )) )
                return notify_fail("你现在不用吃这宝贝!\n");
       this_player()->receive_curing("qi",200);
       message_vision("$N小心地吃下一株雪莲,顿时觉得神清气爽了不少!\n",
                      this_player());

       destruct(this_object());
       return 1;
}
