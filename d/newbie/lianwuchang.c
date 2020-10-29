inherit ROOM;

void create()
{
        set("short", "练武场");
        set("long", @LONG
这是古村的练武场，一个露天的场地里摆满了练武用的沙袋和
木人，几个年轻小伙正在一位老者的知道下呼呼生风地挥动着拳脚。
LONG);
        set("exits", ([
                "north" : __DIR__"bingqishi",
                "south" : __DIR__"xiuxishi",
                "west" : __DIR__"road2",
                "east" : __DIR__"houcun-road",
        ]));

        set("objects", ([
                __DIR__"npc/wubo" : 1,
        ]));
        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("no_fight", 1);
        set("no_fight", 1);
        set("no_pk", 1);
	setup();

        replace_program(ROOM);
}
