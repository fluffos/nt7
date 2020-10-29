inherit ROOM;

void create()
{
        set("short", "紫竹林");
        set("long", @LONG
你来到一片翠绿的紫竹林中，四周全被紫竹所包围，你仿似迷失
了方向。耳旁不时传来一阵阵悦耳的鸟叫声，不禁让人感到心旷神怡。
LONG );
        set("outdoors", "jingzhou");

        set("exits", ([
                "northup" : __DIR__"shijie",
                "south" : __DIR__"zizhulin1",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -7090);
	set("coor/y", -2090);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}