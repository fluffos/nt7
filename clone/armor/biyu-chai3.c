#include <armor.h>
#include <ansi.h>

inherit HAIRPIN;

void create()
{
        set_name(HIG "碧玉钗" NOR, ({ "biyu chai3", "biyu", "chai3" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "只");
                set("value", 200000);
                set("material", "stone");
                set("armor_prop/armor", 1);
                set("armor_prop/dex", 2);
                set("limit", ([
                        "exp":  2000000,
                        "sex" : 1, // 1 为女性
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}