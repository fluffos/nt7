// Room: xiaolu3.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "青石小路");
	set("long", @LONG
这是由青石铺成的小路，路面上夹杂着一些泥沙，小路两边长着一些野草，
开出来的野花飘着阵阵花香。四周是阴森森的原始老林，不时传来一阵阵的野
兽叫声, 头顶有一些不知名的小鸟在跳来跳去。
LONG
	);
	set("exits", ([ 
	    "southdown" : __DIR__"xiaolu2",
	    "northup" : __DIR__"xiaolu4",
        ]));

        set("outdoors", "大理");

	setup();
}