#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + MAG "测试物品" NOR, ({"test object"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", MAG "这是一件测试物品，还没有被巫师创造成形，却发出淡淡紫光。\n" NOR);
                set("unit", "个");
                set("value", 1);
                                set("no_drop", 1);
                                set("no_sell", 1);
                                set("no_give", 1);
                                set("no_get", 1);
        }
}

int query_autoload()
{
        return 1;
}
