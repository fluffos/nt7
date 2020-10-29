inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "暗杀名单" NOR, ({"ansha mingdan", "ansha", "mingdan"}));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "份");
                set("long", HIR "这是一份写有朝廷要员名字的暗杀名单。\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}