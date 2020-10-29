#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIW "明王像" NOR, ({ "mingwang xiang", "mingwang", "xiang" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "paper");
                set("unit", "尊");
                set("long", HIW "一尊拇指般大小的佛像。\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/fy", 2);

        }
        setup();
}

int query_autoload()
{
        return 1;
}