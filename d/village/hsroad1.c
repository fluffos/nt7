inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一条青石大道上，人来人往非常繁忙，不时地有人骑着马
匆匆而过。大道两旁有一些小货摊，似乎是一处集市。南边通向洛阳
古城。
LONG );
        set("outdoors", "village");
        set("exits", ([
                "north" : __DIR__"hsroad2",
                "south" : "/d/changan/road2",
        ]));
        set("objects", ([
                __DIR__"npc/girl" : 4,
        ]));

        setup();
        replace_program(ROOM);
}