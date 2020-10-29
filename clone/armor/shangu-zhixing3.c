#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIC "山谷之星" NOR, ({ "shangu zhixing3", "shangu", "zhixing3" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "串");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/armor", 200);
                set("armor_prop/dex", 4);
                set("armor_prop/str",4);
                set("limit", ([
                        "exp"   :  1500000,
                        "dex"   :  30,
                        "int"   :  30,
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}