// Room: maowu.c

inherit ROOM;

void create()
{
        set("short", "茅屋");
        set("long", @LONG
你穿过内堂来到山腰，不远处有一茅屋。远处望去，千叶
重台，万山苍翠，清溪飞瀑，映带其间，极目烟波千里，映照
峰峦岩岭。近处青苔绿草，苍润欲流，经日头一照，丝毫不觉
灼热，反而清凉怡人，万紫姹红，点缀其间，直如世外桃源！
LONG
        );
       set("no_fight", 1);
        set("exits", ([ /* sizeof() == 2 */
  "northeast" : __DIR__"liupeng",
  "southwest" : __DIR__"diecong4",
]));
        set("objects", ([ 
//  __DIR__"npc/hu" : 1,
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
