
#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "战靴之魂" NOR, ({"boots soul3", "boots", "soul3"}));
        set_weight(100);

        set("long", HIM "这是一个战靴之魂。\n" NOR);
        set("unit", "个");
        set("value", 200000);
        set("no_sell", 1);

        set("type", "boots");
        set("status", 3);
        set("auto_load", 1);
        
        setup();
}

