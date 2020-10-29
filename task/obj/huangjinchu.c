#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIY "黄金杵" NOR,({ "huangjin chu" }) ); 
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "把");
                set("material", "cloth");
                set("long", "这是一把黄金杵。\n");
        }
        set("owner", "达尔巴");
        setup();
}

