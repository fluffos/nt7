#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "镶嵌符" NOR, ({ "enchase symbol", "symbol" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIR "此符文具有使镶嵌宝物时候拥有100%成功率。\n" NOR);
                set("unit", "张");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

