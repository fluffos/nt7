
#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "RP_NAME之魂" NOR, ({"RP_ID soulRP_STATUS", "RP_ID", "soulRP_STATUS"}));
        set_weight(100);

        set("long", HIM "这是一个RP_NAME之魂。\n" NOR);
        set("unit", "个");
        set("value", 200000);
        set("no_sell", 1);

        set("type", "RP_ID");
        set("status", RP_STATUS);
        set("auto_load", 1);
        
        setup();
}

