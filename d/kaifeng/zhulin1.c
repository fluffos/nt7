inherit ROOM;

void create()
{
        set("short", "小茅屋");
        set("long", @LONG
你走进竹林中的小茅屋，打量了一下，在茅屋仅是用茅草覆顶，
四边的墙壁是用一根根大毛竹打入地下而成的，屋中的桌椅也都是翠
竹所制，桌上放的茶壶是用整个竹根雕成的。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out" : __DIR__"zhulin",
        ]));

	set("coor/x", -5021);
	set("coor/y", 2139);
	set("coor/z", 9);
	setup();
        replace_program(ROOM);
}