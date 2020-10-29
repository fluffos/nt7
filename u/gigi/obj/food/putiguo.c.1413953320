// apple.c
#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
        set_name(HIG"菩提果"NOR, ({"puti guo","bodhi fruit"}));
        set_weight(4000);
        set("long", "一个清亮翠绿菩提果，看上去很鲜美的样子。\n");
        set("unit", "个");
        set("life", 7);
        set("value", 0);
        set("fruit_remaining", 4); //可以吃4口
        set("food_supply", 15);   //每口加15的food
        set("water_supply", 4);  //每口可以加4的water
        //每次吃的msg,没有也可以的。
        set("eat_msg", "$N拿起$n，大大的咬了一口。\n"); 
        //最后一口的msg，没有亦可
        set("end_msg", "$N三口两口吃完了这个$n。\n");  
        //吃饱了的msg, 没有亦可，但不能有代词。
        set("over_msg", "吃这么多？小心撑破肚皮！！！！\n"); 
        // 水果吃完剩下的东西 :-)
        set("core", "菩提果核");         //name
        set("core_id", ({"puti hu", "bodhi core", "hu", "core"}) ); //id
        set("core_unit", "个");        //unit
        set("core_long", "一个菩提果核。\n"); //long
        set("gifts", ([
                "int" : 1,
                "spi" : 1,
                "per" : 1,
        ]));
        setup();
}
