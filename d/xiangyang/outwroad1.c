// /d/xiangyang/outwroad1.c

inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一条青石大道上，人来人往非常繁忙，不时有人骑着马匆
匆而过。大道东边通向襄阳城，南面一条小路通向一个山丘，西边是
一条小河。
LONG );
        set("outdoors", "襄阳");

        set("exits", ([
              "southeast" : __DIR__"westgate1",
        ]));

        setup();
        replace_program(ROOM);
}
