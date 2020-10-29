#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIW "软猬甲" NOR,({ "ruanwei jia" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "件");
                set("material", "silk");
                set("long", "这是一件软猬甲。\n");
        }
        set("owner", "黄蓉");
        setup();
}

