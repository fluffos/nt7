#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIR "阴阳合欢散" NOR,({ "yinyang hehuansan" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "包");
                set("material", "wood");
                set("long", "这是一包阴阳合欢散。\n");
        }
        set("owner", "段延庆");
        setup();
}  
