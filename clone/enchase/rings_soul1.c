
#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "戒指之魂" NOR, ({"rings soul1", "rings", "soul1"}));
        set_weight(100);

        set("long", HIM "这是一个戒指之魂。\n" NOR);
        set("unit", "个");
        set("value", 200000);
        set("no_sell", 1);

        set("type", "rings");
        set("status", 1);
        set("auto_load", 1);
        
        setup();
}

