#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIY "无为" NOR, ({ "wu wei3", "wu", "wei3" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "串");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/joblv", 1);
                set("armor_prop/damage", 100);
                set("armor_prop/str", 5);
                set("special/desc", HIR "可破格提升转世职业技能1级。" NOR);
                set("limit", ([ 
                                        "exp" : 40000000,
                                        "scborn" : 1,
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}