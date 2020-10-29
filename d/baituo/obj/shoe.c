#include <ansi.h> 
#include <armor.h>
inherit ITEM;

void create()
{
        set_name("绣花鞋", ({ "xiuhua xie", "xiuhua", "xie", "shoe" }));
        set_weight(300);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "只");
                set("long", HIM "这是一只漂亮的绣花鞋。\n" NOR);
                set("value", 50);
                set("material", "cloth");
                set("female_only", 1);
                set("armor_prop/armor", 3);
        }
}