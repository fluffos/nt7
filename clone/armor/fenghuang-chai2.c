#include <armor.h>
#include <ansi.h>

inherit HAIRPIN;

void create()
{
        set_name(HIR "凤凰金钗" NOR, ({ "fenghuang chai2", "fenghuang", "chai2" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "只");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/armor", 1);
                set("armor_prop/int", 5);
                set("armor_prop/con", 3);
                set("limit", ([
                        "sex" : 1, // 1 为女性
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}