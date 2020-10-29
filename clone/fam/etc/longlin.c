#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "龍鳞" NOR, ({ "dragon palta", "palta" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "一片龍鳞，光彩夺目。\n" NOR);
                set("unit", "片");
                set("value", 100000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}