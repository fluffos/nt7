inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "富士山风景画" NOR, ({"fengjing hua", "fengjing", "hua"}));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "副");
                set("long", HIW "这是一副绘着富士山风景的图画。\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}