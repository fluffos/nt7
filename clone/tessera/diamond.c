#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIW "水晶钻" NOR, ({ "diamond" }));
        set_weight(20);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", WHT "这是一颗宝石，上面似乎附着某种神奇的魔力。\n" NOR);
                set("value", 100000);
                set("unit", "颗");
                set("level", 2); 
                set("material", "diamond"); 
                set("no_identify", 1);
        }
        setup();
}
