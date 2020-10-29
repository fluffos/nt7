inherit ROOM;

void create()
{
        set("short", "小巷尽头");
        set("long", @LONG
这是一条又深又黑的巷子，散发出一阵阵污水的味道和食物发霉
的味道，又脏又臭。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "north" : __DIR__"xxiang",
                "south" : __DIR__"yuanmiaoguan",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/qigai" : 2,
                "/d/beijing/npc/dipi" : 1,
        ]));
        set("coor/x", -7080);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}