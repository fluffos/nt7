#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(NOR + YEL"神雕羽毛" NOR, ({ "shendiao yumao", "shendiao", "yumao" }) );
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "steel");
                set("unit", "根");
                set("long", HIM "这是一根神雕神上的羽毛，越一米来长。\n" NOR);
                set("value", 35000);
                set("limit", ([
                        "exp"    :   100000,
                ]));
                set("armor_prop/dex", 1);
                set("armor_prop/int", 1);
                set("armor_prop/con", 1);
                set("armor_prop/str", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}