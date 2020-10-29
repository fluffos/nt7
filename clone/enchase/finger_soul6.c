
#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "指套之魂" NOR, ({"finger soul6", "finger", "soul6"}));
        set_weight(100);

        set("long", HIM "这是一个指套之魂。\n" NOR);
        set("unit", "个");
        set("value", 200000);
        set("no_sell", 1);

        set("type", "finger");
        set("status", 6);
        set("auto_load", 1);
        
        setup();
}

