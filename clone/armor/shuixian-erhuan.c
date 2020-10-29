#include <armor.h>
#include <ansi.h>

inherit EARRING;

void create()
{
        set_name(HIC "水仙耳环" NOR, ({ "shuixian erhuan", "shuixian", "erhuan" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "副");
                set("value", 200000);
                set("material", "silver");
                set("armor_prop/armor", 1);
                set("armor_prop/fy", 1);
                set("limit", ([
                        "sex" : 1, // 1 为女性
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}