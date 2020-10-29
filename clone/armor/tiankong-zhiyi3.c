#include <armor.h>
#include <ansi.h>

inherit SURCOAT;

void create()
{
        set_name(HIW "天空之翼" NOR, ({ "tiankong zhiyi3", "tiankong", "zhiyi3" }) );
        set_weight(2000);
        set("long", HIW "这是一件白色的披风，上绘蓝天白云，飘逸之极。\n" NOR);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("material", "steel");
                                set("value", 3000000);
                set("armor_prop/armor", 200);
                                set("armor_prop/dex", 10);
                                set("armor_prop/int", 3);
                                set("armor_prop/dodge", 40);
                                set("special/desc", HIR "提升有效轻功40级。");
                                set("limit", ([ 
                                        "exp" : 18000000,
                                        "scborn" : 1,
                                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}