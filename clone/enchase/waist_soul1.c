
#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "腰带之魂" NOR, ({"waist soul1", "waist", "soul1"}));
        set_weight(100);

        set("long", HIM "这是一个腰带之魂。\n" NOR);
        set("unit", "个");
        set("value", 200000);
        set("no_sell", 1);

        set("type", "waist");
        set("status", 1);
        set("auto_load", 1);
        
        setup();
}

