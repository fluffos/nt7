// Room: gbdixiaoshi.c
// by aji

inherit ROOM;
void create()
{
        set("short", "林间小屋");
        set("long", @LONG
你走进了一间小屋。四周墙壁都由青竹篾编成，窗外是一望无际
的竹林。屋里的桌椅、床铺均为竹制。但一阵扑鼻而来的狗肉香味，
却显得与这清雅的气纷格格不入。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "west" : "/d/city/gbandao"
        ]));
	set("objects", ([
		"/d/city/obj/zhubang": 1,
		"/d/city/obj/gourou": 1,
		"/d/city/obj/jiudai": 1,
		"/d/city/obj/jitui": 1
	]));

        set("valid_startroom", 1);
        set("sleep_room", 1);
	set("coor/x", 50);
	set("coor/y", 40);
	set("coor/z", 0);
	setup();

        (CLASS_D("gaibang") + "/hong")->come_here();
}

void reset()
{
        ::reset();
        (CLASS_D("gaibang") + "/hong")->come_here();
}