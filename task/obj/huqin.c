#include <ansi.h>
inherit TASK;
void create()
{
        set_name(YEL "胡琴" NOR,({ "hu qin" }) ); 
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "把");
                set("material", "wood");
                set("long", "这是一把普通的胡琴。\n");
        }
        set("owner", "莫大");
        setup();
}

