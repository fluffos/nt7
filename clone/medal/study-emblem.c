#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(MAG "紫金读书勋章" NOR, ({ "study emblem", "emblem" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", MAG "带在身上可以提升读书最大次数三百次。\n" NOR);
                set("unit", "块");
                set("can_summon", 1);
                set("no_sell", 1);
                set("value", 500000);
                set("material", "gold");
                set("armor_prop/study_times", 300);
        }
        set("enchase/SN", "ds1");
        set("auto_load", 1);
        setup();
}