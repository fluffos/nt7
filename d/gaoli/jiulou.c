// /d/gaoli/jiulou
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "天外天");
        set("long", @LONG
这里便是高丽首曲一指的酒楼天外天了。在一楼的大厅中摆放了十
数张圆桌，旁边坐满了客人。几名店小二达这雪白的毛巾在客人中穿梭
着，好一派生意兴隆的景象。
LONG
);
set("exits", ([
                "west":__DIR__"zhuque-1", 
        ]));
set("objects", ([
                "/d/gaoli/npc/han" : 1,
        ]));
       setup();
        replace_program(ROOM);
}
