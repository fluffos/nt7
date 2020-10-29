
#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "武器之魂" NOR, ({"weapon soul5", "weapon", "soul5"}));
        set_weight(100);

        set("long", HIM "这是一个武器之魂。\n" NOR);
        set("unit", "个");
        set("value", 200000);
        set("no_sell", 1);

        set("type", "weapon");
        set("status", 5);
        set("auto_load", 1);
        
        setup();
}

