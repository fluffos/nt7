// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一条山路上。南边就是高丽的玉龙门了。这里的行人不是很
多。看来平时很少有人到这里来。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"shanlu9",
                "northwest":__DIR__"shanlu11",
        ]));
       setup();
        
}

