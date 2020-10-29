// Room: /city/zahuopu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "杂货铺");
        set("long", @LONG
这是一家小小的杂货铺，大箱小箱堆满了一地，都是一些日常用
品。杨掌柜懒洋洋地躺在一只躺椅上，招呼着过往行人。据说私底下
他也卖一些贵重的东西。摊上立着一块招牌(zhaopai)。
LONG );
	set("item_desc", ([
		"zhaopai": "请用 \"list\" 列出货物表，\"buy\" 向老板购物。\n",
	]));
	set("exits", ([
		"north" : "/d/city/dongdajie1",
		"up"    : "/d/city/garments",
	]));
    set("no_fight",1);
    set("no_steal",1);
	set("objects", ([
		"/d/city/npc/yang": 1,
	]));
	set("coor/x", 10);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}