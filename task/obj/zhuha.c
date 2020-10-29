#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIG "莽牯朱蛤" NOR,({ "zhu ha" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "个");
                set("material", "wood");
                set("long", "这是一个莽牯朱蛤。\n");
        }
        set("owner", "段誉");
        setup();
}

