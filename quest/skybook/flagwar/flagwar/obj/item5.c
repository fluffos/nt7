#include <ansi.h>

inherit ITEM; 

void create()
{
	      set_name(HIG"抢旗战 - "HIW"惊雷符"NOR, ({"fwar count seal","seal"}) );
        set_weight(300);
        set("unit", "个");
        set("long", "抢旗战专用特殊物品，放在身上在死亡时会自动使用。\n");
        set("value", 1);
        set("no_store",1);
        set("no_sell", 1);
        set("flag_war_item", 1);
 //       set("no_get", 1);
        set("no_drop", 1);
        setup();
}