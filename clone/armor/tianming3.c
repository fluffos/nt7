#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIR "天命" NOR, ({ "tian ming3", "tian", "ming3" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "串");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/damage", 200);
                set("armor_prop/con", 6);
                set("armor_prop/dex", 6);
                set("armor_prop/str", 8);
                set("armor_prop/int", 4);
                set("limit", ([ 
                                        "exp" : 35000000,
                                        "scborn" : 1,
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}