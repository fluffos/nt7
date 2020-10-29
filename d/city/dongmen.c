// Room: /city/dongmen.c
// YZC 1995/12/04 

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "东门");
        set("long", @LONG
这是东城门，城门正上方刻着『东门』两个楷书大字，城墙上贴
着几张官府告示(gaoshi)。官兵们警惕地注视着过往行人，你最好小
心为妙。一条笔直的青石板大道向东西两边延伸。东边是郊外，隐约
可见一片一望无际的树林，神秘莫测。西边是城里。北面有一片茂盛
的青竹林。
LONG );
        set("outdoors", "city");
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
	set("exits", ([
		"east" : "/d/taishan/yidao",
		"north" : "/d/city/ml1",
		"south" : "/d/city/jiaowai1",
		"west" : "/d/city/dongdajie3",
	]));
	set("objects", ([
		"/d/city/npc/wujiang" : 1,
		"/d/city/npc/bing" : 2,
                "/d/city/npc/jpl2": 1,
	]));

	set("coor/x", 40);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n扬州知府\n程药发\n";
}