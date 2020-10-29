#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIG "精致花盆" NOR,({ "hua pen" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "个");
                set("material", "stone");
                set("long", "这是一个精致花盆。\n");
        }
        set("owner", "华赫艮");
        setup();
}

