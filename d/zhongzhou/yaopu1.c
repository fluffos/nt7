inherit ROOM;

void create()
{
        set("short", "药铺内院");
        set("long", @LONG
这里就是药铺内院，你一走进来就觉得一股热浪。只见十
几只炉子都在熬药，有几个药铺的伙计在忙碌着。你要熬药的
话就要依着药方把放进药罐里。
LONG);
        set("exits", ([
                "north" : __DIR__"yaopu",
                
        ]));

        set("coor/x", -9030);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}