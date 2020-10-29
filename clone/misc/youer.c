#include <ansi.h>
inherit COMBINED_ITEM; 

void create()
{
        set_name(HIY "诱饵" NOR, ({ "you er","you", "er" }));
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是专门用来引诱各种禽兽的。 \n");
                set("base_unit", "块"); 
                set("base_weight", 30); 
                set("base_value", 1000); 
                set("no_sell", "这野兽吃的东西你也给我？"); 
                set("lure", 1);
                set("level", 10);
        }
        set_amount(1);
        setup();
}