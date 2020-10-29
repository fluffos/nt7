
#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "项链之魂" NOR, ({"neck soul1", "neck", "soul1"}));
        set_weight(100);

        set("long", HIM "这是一个项链之魂。\n" NOR);
        set("unit", "个");
        set("value", 200000);
        set("no_sell", 1);

        set("type", "neck");
        set("status", 1);
        set("auto_load", 1);
        
        setup();
}

