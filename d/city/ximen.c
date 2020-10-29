// Room: /city/ximen.c
// YZC 1995/12/04 

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "西门");
        set("long", @LONG
这是西城门，几年前曾经遭到土匪的攻打，因此显得有些破败。
城门正上方勉勉强强可以认出『西门』两个大字，城墙上贴着几张通
缉告示(gaoshi)。    这里是罪犯逃往西域的必经之地，官兵们戒备
森严，动不动就截住行人盘问。一条笔直的青石板大道向东西两边延
伸。西边是郊外，骑马的、坐轿的、走路的，行人匆匆。东边是城里。
LONG );
        set("outdoors", "city");
//	set("no_clean_up", 0);
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));

	set("exits", ([
		"east"  : "/d/city/xidajie3",
		"west"  : "/d/city/ximenroad",
                "south" : "/d/city/xiaofang",
	]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
                "/d/mingjiao/npc/fenggongying" : 1,
        ]));
	set("coor/x", -40);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n扬州知府\n程药发\n";
}