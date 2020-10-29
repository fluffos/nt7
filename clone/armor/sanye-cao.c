#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIG "三叶草" NOR, ({ "sanye cao", "sanye", "cao" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "paper");
                set("unit", "片");
                set("long", HIG "这是一片有三片叶子的青草，乃扶桑国幸运草。\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/qy", 3);

        }
        setup();
}

int query_autoload()
{
        return 1;
}