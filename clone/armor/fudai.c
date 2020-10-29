#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIR "福袋" NOR, ({ "fu dai", "fu", "dai" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "paper");
                set("unit", "个");
                set("long", HIR "扶桑国有绣制福袋的习俗，据说带在身边可以逢凶化吉。\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/fy", 3);

        }
        setup();
}

int query_autoload()
{
        return 1;
}