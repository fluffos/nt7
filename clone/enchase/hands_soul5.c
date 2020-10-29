
#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "铁掌之魂" NOR, ({"hands soul5", "hands", "soul5"}));
        set_weight(100);

        set("long", HIM "这是一个铁掌之魂。\n" NOR);
        set("unit", "个");
        set("value", 200000);
        set("no_sell", 1);

        set("type", "hands");
        set("status", 5);
        set("auto_load", 1);
        
        setup();
}

