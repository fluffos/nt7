#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIC "四十二章经" NOR,({ "sishier jing" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "套");
                set("material", "paper");
                set("long", "这是一套四十二章经。\n");
        }
        set("owner", "韦小宝");
        setup();
}
