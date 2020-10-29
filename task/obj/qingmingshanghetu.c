#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIW "清明上河图" NOR,({ "qingming shanghetu" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "张");
                set("material", "paper");
                set("long", "这是一张清明上河图。\n");
        }
        set("owner", "冯老狗");
        setup();
}

