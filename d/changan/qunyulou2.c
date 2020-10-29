//Room: qunyulou2.c

inherit ROOM;

void create()
{
        set("short", "群玉楼二楼");
        set("long", @LONG
群玉楼二楼。这是一座三层高的小楼，本来是某一位大亨陪同夫
人赏月之处，现在已被群玉楼用重金买下。只听一声声划拳行令，加
杂着女人的娇笑，不时的从房间中传出。
LONG );
        set("exits", ([ /* sizeof() == 6 */
                "north" : "/d/changan/qunyuys1",
                "south" : "/d/changan/qunyuys2",
                "west"  : "/d/changan/qunyuys3",
                "east"  : "/d/changan/qunyuys4",
                "down"  : "/d/changan/qunyulou1",
                "up"    : "/d/changan/qunyulou3",
        ]));

        set("coor/x", -10710);
	set("coor/y", 1950);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}