// Room: /city/nandajie2.c
// YZC 1995/12/04 
// CLEANSWORD 1996/2/2

inherit ROOM;

void create()
{
	set("short", "南大街");
        set("long", @LONG
你走在一条繁华的街道上，向南北两头延伸。南边是南城门，北
边通往市中心，西边是一家顾客众多的茶馆，三教九流人士都在那里
谈天说地。东边的扬州有名的喝花酒的地方——丽春院。丽春院白天
门可罗雀，但是到了晚上却是热闹非凡。隐约可以听见那两层的楼房
内传来阵阵女子的浪笑声，让你心头一荡。
LONG );
        set("outdoors", "city");
	set("exits", ([
		"east"  : "/d/city/lichunyuan",
		"south" : "/d/city/nanmen",
		"west"  : "/d/city/chaguan",
		"north" : "/d/city/nandajie1",
	]));
        set("objects", ([
                CLASS_D("shaolin") + "/tuoboseng" : 1,
        ]));
	set("coor/x", 0);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
}