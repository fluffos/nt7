#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIY "金钗" NOR,({ "jin chai" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "个");
                set("material", "stone");
                set("long", "这是个造型独特的金钗。\n");
        }
        set("owner", "王语嫣");
        setup();
}

