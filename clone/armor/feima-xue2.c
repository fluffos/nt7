#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIW "飞马靴" NOR, ({ "feima xue2", "feima", "xue2" }) );
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "双");
                set("long", HIW "一双做工奇特人间罕见的宝靴子，蕴藏着神奇的力量。\n");
                set("value", 2000000);
                set("armor_prop/armor", 200);
                                set("armor_prop/dex", 3); //后天身法+1
                                set("armor_prop/int", 2); //后天悟性+2
                set("material", "boots");
                                set("limit", ([
                                        "exp"  :  30000000,
                                        "dex"  :  60,
                                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}