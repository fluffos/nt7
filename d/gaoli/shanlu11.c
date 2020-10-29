// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一条山路上。再往南边走不远就是高丽的玉龙门了。这里的
行人不是很多。看来平时很少有人到这里来。向北望去，隐约可以看到
高丽的烽火台。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"shanlu10",
                "north":__DIR__"shanlu12",
        ]));
       setup();
        
}

