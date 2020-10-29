// mcrystal.c 神之水晶

#include <ansi.h>
#include <armor.h>

inherit TESSERA;

void create()
{
        set_name(HIM "神之水晶" NOR, ({ "magic crystal" }) );
        set_weight(50);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIM "一块闪烁这奇异光芒的粉色水晶，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("value", 200000);
                set("unit", "块");
                set("level", 4);
                set("no_identify", 1);
        }
        setup();
}