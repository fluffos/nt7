#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIC "兽骨" NOR, ({ "shou gu", "shou", "gu" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "paper");
                set("unit", "块");
                set("long", HIC "远古巨兽的骸骨所制成的护身链。\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/qy", 2);

        }
        setup();
}

int query_autoload()
{
        return 1;
}