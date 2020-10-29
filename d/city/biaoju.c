// Room: /city/biaoju.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "福威镖局");
        set("long", @LONG
你来到一座结构宏伟的建筑前，左右石坛上各插着一根两丈多高
的旗杆，杆上青旗飘扬。右首旗子用金线绣着一头张牙舞爪的狮子，
狮子上头有一只蝙蝠飞翔。左首旗子上写着『福威镖局』四个黑字，
银钩铁划，刚劲非凡。入口处排着两条长凳，几名镖头坐着把守。少
镖头正跟他们说笑。
LONG );

	set("exits", ([
		"south" : __DIR__"zhengting",
                "north" : __DIR__"xidajie3",
	]));
	set("objects", ([
		__DIR__"npc/biaotou" : 2,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -30);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}