
#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "护甲之魂" NOR, ({"armor soul1", "armor", "soul1"}));
        set_weight(100);

        set("long", HIM "这是一个护甲之魂。\n" NOR);
        set("unit", "个");
        set("value", 200000);
        set("no_sell", 1);

        set("type", "armor");
        set("status", 1);
        set("auto_load", 1);
        
        setup();
}

