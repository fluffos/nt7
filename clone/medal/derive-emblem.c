#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(MAG "紫金汲取勋章" NOR, ({ "derive emblem", "emblem" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", MAG "带在身上可以提升300点汲取速度的效果。\n" NOR);
                set("unit", "块");
                set("can_summon", 1);
                set("value", 500000);
                set("material", "gold");
                set("armor_prop/derive_times", 300);
        }
        set("enchase/SN", "jq1");
        set("auto_load", 1);
        setup();
}