#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIW "乌龟狗香香" NOR,({ "hei gourou" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "份");
                set("material", "wood");
                set("long", "这是一份乌龟狗香香。\n");
        }
        set("owner", "杨小邪");
        setup();
}

