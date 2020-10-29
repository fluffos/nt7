// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一条山路上。再往南边走不远就是高丽的玉龙门了。几乎没
有什么人，冷冷清清的。这里已经是高丽的北郊了。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"shanlu11",
                "north":__DIR__"shanlu13",
                "west":__DIR__"shanlu14",
        ]));
       setup();
        
}

