#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIC "花雕酒袋" NOR,({ "huadiao jiudai" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "个");
                set("material", "stone");
                set("long", "这是一个花雕酒袋。\n");
        }
        set("owner", "金老板");
        setup();
}

