// mcrystal.c 神之水晶

#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIM "神之水晶" NOR, ({ "magic crystal" }) );
        set_weight(50);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIM "一块闪烁这奇异光芒的粉色水晶，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("value", 200000);
                set("unit", "块");
                set("can_be_tessera", 1);
                set("level", 4);
                set("material", "mcrystal"); 
                set("magic/type", "magic");
                set("magic/power", 500);
                set("auto_load", 1); 
        }
        set("enchase/weapon_prop/add_magic", 3); 
        set("enchase/rings_prop/add_magic", 3); 
        set("enchase/armor_prop/reduce_magic", 1); 
        setup();
}
