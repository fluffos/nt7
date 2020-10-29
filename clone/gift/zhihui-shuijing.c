// 智慧水晶 与同伴系统关联 参考文件 help mater

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "智慧水晶" NOR, ({ "zhihui shuijing" }) );
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", HIM "一块粉色的水晶碎片，你的同伴最喜欢。\n" NOR);
                set("value", 1);
                set("unit", "块");
        }
        setup();
}

int query_autoload() { return 1; }