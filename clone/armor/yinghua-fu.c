#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIM "樱花符" NOR, ({ "yinghua fu", "yinghua", "fu" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "paper");
                set("unit", "张");
                set("long", HIM "一张粉红色的灵符，上面绘有扶桑樱花的图画。\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/qy", 1);

        }
        setup();
}

int query_autoload()
{
        return 1;
}