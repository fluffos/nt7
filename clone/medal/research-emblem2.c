#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(MAG "钻石研究勋章" NOR, ({ "research emblem2", "emblem2" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", MAG "带在身上可以提升研究最大次数五百次。\n" NOR);
                set("unit", "块");
                set("can_summon", 1);
                set("value", 500000);
                set("material", "diamond");
                set("armor_prop/research_times", 500);
        }
        set("enchase/SN", "yj2");
        set("auto_load", 1);
        setup();
}