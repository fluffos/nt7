// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一条山路上。南边就是高丽的玉龙门了。这里的地形起伏，
有些崎岖。这里的行人比较多。有几个人正在附近挖野菜。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southwest" : __DIR__"shanlu6",
                "north":__DIR__"shanlu8",
        ]));
       setup();
        
}

