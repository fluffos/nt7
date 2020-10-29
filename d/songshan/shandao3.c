// Room: /d/songshan/shandao3.c
// Last Modified by Lonely on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "嵩岳山道");
        set("long", @LONG
你走在嵩岳山道，青松翠柏，山风岚雾，时来飘荡。远望山下犬吠
鸡啼，顿起仙凡之感。
LONG );
        set("exits", ([
                "northup"   : __DIR__"songyuesi",
                "southeast" : __DIR__"shuyuan",
        ]));
        set("objects", ([
                __DIR__"npc/zhao": 1,
        ]));
        set("outdoors", "songshan");
        set("coor/x", -20);
        set("coor/y", 780);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}