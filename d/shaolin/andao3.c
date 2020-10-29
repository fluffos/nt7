// Room: /d/shaolin/andao3.c
// Date: YZC 96/02/06
// redl 2014

#include <login.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "暗道");
        set("long", @LONG
这是一个阴暗潮湿的地道，四壁用粗糙的片岩垒垛而成，一颗颗
水珠沿着墙壁滚下来，溅在地上。也许是因为长时间无人通行的缘故，
整个地道弥漫着一股腐尸般的恶臭。
LONG );
        set("exits", ([
                //"up" : __DIR__"zhonglou1",
                "enter" : __DIR__"bagua0",
        ]));
        set("no_clean_up", 0);
                     set("no_protect", 1);
                     set("no_rideto", 1); 
                     set("no_flyto", 1); 
                     set("no_fly", 1);
                     set("no_sleep_room", 1);
                     set("no_magic", 1);  
        setup();
}

void init()
{
        object me = this_player();
        if (query_temp("hantan/done", me) &&
                !query("exits/up")
                ) {
                /*if ( query("level", me) < 80 )
                {
                        return notify_fail("你试着推了推顶上的砖盖，触手冰凉，纹丝不动。\n" 
                        + "看来已被铁汁浇透，坚如铁板一般。看来你只能另想办法了。\n");
                        me->start_busy(3);
                } */               
                message_vision( HIY
                "$N全身琉璃真气运转，拔身错步，嘿地一声，举起双掌向上猛击。\n"
                "只见一股白气自$N掌心而出，迅猛无比地击中顶上的铁铸砖盖。\n"
                "克剌剌一声巨响，砖盖被震成无数小碎片四散飘飞。露出一个向上的洞口。\n" NOR, me );
                 set("exits/up", __DIR__"zhonglou1");
        }
        
}

