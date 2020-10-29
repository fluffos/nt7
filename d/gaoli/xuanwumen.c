// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "玉龙门");
        set("long", @LONG
这里是高丽的玉龙门。南面就到了城中，远望人山人海，往来行人
车流不绝。北面一条大路通向何方。城门下有一些执勤的兵士。兵将警
惕的盯着往来人士。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"xuanwu-2",
                "north" : __DIR__"shanlu1",
                "northeast":__DIR__"shanlu6",
                "northwest":__DIR__"shanlu9",
        ]));
set("objects",([
  __DIR__"npc/guanbing":4,
  __DIR__"npc/wujiang":1,
  ]));
       setup();
        
}

