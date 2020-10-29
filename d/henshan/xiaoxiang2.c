inherit ROOM;

void create()
{
        set("short", "小巷");
        set("long", @LONG
这是衡阳城内一条偏僻的小巷，平时很少有人来，只见这条小巷
弯弯曲曲不知道通向何处。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "south"  : __DIR__"baihuzhai",
                "north"  : __DIR__"xiaoxiang1",
        ]));

	set("coor/x", -6880);
	set("coor/y", -5720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
