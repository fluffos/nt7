// /d/gaoli/xuanwumen
// Room in 高丽
inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这里是一条山路。这里的山路崎岖曲折，很难找到出路。一不小心，
就可能滚落下去。向东望去，可以看到高丽城的全貌。
LONG
        );

        set("exits", ([
                "eastdown" : __DIR__"shanlu3",
                "northup":__DIR__"shanlu5",
        ]));

         set("outdoors", "gaoli");
        setup();
        replace_program(ROOM);
}


