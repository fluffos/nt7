
#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIG "江户战衣" NOR, ({ "jianghu zhanyi", "jianghu", "zhanyi" }) );
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("long", HIG "扶桑江户所产的战衣，乃德川家族所特有，战衣上均绣有「德川」的字样。\n" NOR);
                set("material", "steel");
                set("value", 800000);
                set("armor_prop/armor", 600);

        }
        setup();
}

int query_autoload()
{
        return 1;
}