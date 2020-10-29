#include <armor.h>
#include <ansi.h>

inherit SURCOAT;

void create()
{
        set_name(HIG "蝉翼披风" NOR, ({ "chanyi pifeng", "chanyi", "pifeng" }) );
        set_weight(1);
        set("long", HIG "东方不败所穿戴的披风，薄如蝉翼，飘逸无比。\n" NOR);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("material", "paper");
                set("value", 3000000);
                set("armor_prop/armor", 100);
                set("armor_prop/dex", 200);
                set("armor_prop/int", 50);
                set("armor_prop/str", 70);
                set("armor_prop/damage", 8000);
                set("armor_prop/dodge", 300);
                set("special/desc", HIR "提升有效轻功300级。" NOR);
                set("limit", ([ 
                                        "exp" : 100000000,
                                        "scborn" : 1,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
