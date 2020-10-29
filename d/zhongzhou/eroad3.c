inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
此处往东不远是开封，往西可到中州，不少游人顺着这条路游玩。
LONG);
        set("exits", ([
                "east": "/d/kaifeng/ximen",
                "west" : __DIR__"eroad2",
        ]));
        set("outdoors", "zhongzhou");

        set("coor/x", -8970);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}