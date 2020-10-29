#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIY "金算盘" NOR,({ "jin suanpan" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "个");
                set("material", "stone");
                set("long", "这是个金算盘。\n");
        }
        set("owner", "钱眼开");
        setup();
}

