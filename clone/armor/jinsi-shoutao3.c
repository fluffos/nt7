// shoutao.c  手套

#include <armor.h>
#include <ansi.h>

inherit HANDS;

void create()
{
        set_name(HIW "金丝手套" NOR, ({ "jinsi shoutao3", "jinsi", "shoutao3" }) );
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "双");
                set("long", HIW "这是一双金丝铸造而成的手套，闪闪发亮。\n" NOR);
                set("value", 750000);
                set("material", "gold");
                set("armor_prop/armor", 500);
                set("armor_prop/unarmed_damage", 800);
                set("limit", ([
                        "exp"    :  34000000,
                        "int"    :  60,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}