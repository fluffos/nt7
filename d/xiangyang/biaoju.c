// Room: /d/xiangyang/biaoju.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "福威镖局");
        set("long", @LONG
你来到一座结构宏伟的建筑前，左右石坛上各插着一根两丈多高
的旗杆，杆上青旗飘扬。右首旗子用金线绣着一头张牙舞爪的狮子，
狮子上头有一只蝙蝠飞翔。左首旗子上写着『福威镖局襄阳分号』八
个黑字，银钩铁划，刚劲非凡。入口排着两条长凳，几名镖头坐着把
守。
LONG );
        set("exits", ([
                "west" : __DIR__"eastroad1",
        ]));
        set("objects", ([
                __DIR__"npc/biaotou" : 2,
        ]));
        set("coor/x", -7790);
	set("coor/y", -760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}