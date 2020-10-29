// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一条山路上。再往南边走不远，就可以到高丽的玉龙门了。
这里的道路有些崎岖，你不禁小心起来。向北望去，隐约有一个巨大的
建筑物。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"shanlu7",
                "northeast":__DIR__"guangchang",
        ]));
       setup();
        
}

