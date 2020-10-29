
#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "护身符之魂" NOR, ({"charm soul6", "charm", "soul6"}));
        set_weight(100);

        set("long", HIM "这是一个护身符之魂。\n" NOR);
        set("unit", "个");
        set("value", 200000);
        set("no_sell", 1);

        set("type", "charm");
        set("status", 6);
        set("auto_load", 1);
        
        setup();
}

