#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIW "蒙汗药" NOR,({ "menghan yao" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "包");
                set("material", "wood");
                set("long", "这是一包蒙汗药。\n");
        }
        set("owner", "韦小宝");
        setup();
}  
