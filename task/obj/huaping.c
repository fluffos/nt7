#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIC "青花瓷花瓶" NOR,({ "hua ping" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "个");
                set("material", "stone");
                set("long", "这是一个青花瓷花瓶。\n");
        }
        set("owner", "刘掌柜");
        setup();
}

