inherit ROOM;

void create()
{
        set("short", "西门外");
        set("long", @LONG
这里是北京的西城门外。人来人往，煞是热闹。
LONG );
        set("exits", ([
                "east" : "/d/beijing/xichengmen",
                "west" : "/d/heimuya/road3",
                "north" : "/d/beijing/liandan_lin1",
                "south" : "/d/beijing/liandan_lin2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "beijing");
	set("coor/x", -2860);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}