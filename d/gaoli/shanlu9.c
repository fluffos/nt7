// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一条山路上。南边就是高丽的玉龙门了。有很多行人从你的
身旁走过，说着你听不懂的高丽语。往北边去，可以到高丽的北烽火台。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"xuanwumen",
                "northwest":__DIR__"shanlu10",
        ]));
       setup();
        
}

