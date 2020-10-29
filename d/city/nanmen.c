// Room: /city/nanmen.c
// YZC 1995/12/04 

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "南门");
        set("long", @LONG
这是南城门，城墙被当成了广告牌，贴满了花花绿绿各行各业的
广告，官府的告示(gaoshi)因此不太显目。官兵们被近处的欢声笑语
所吸引，似乎不是很认真在执勤。南边就是渡江桥了。
LONG );
        set("outdoors", "city");
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));

	set("exits", ([
           "south" : "/d/city/dujiangqiao",
		"north" : "/d/city/nandajie2",
		"west"  : "/d/city/jiaowai8",
		"east"  : "/d/city/jiaowai7",
	]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
                "/d/city/npc/shisong" : 1,
        ]));
	set("coor/x", 0);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n扬州知府\n程药发\n";
}