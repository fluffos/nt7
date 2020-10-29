inherit ROOM;

void create()
{
	set("short", "鼓楼");
	set("long", @LONG
这是一座砖木结构的小楼，飞檐翘翎，檐角上挂满了一串串小铜
铃，随风叮叮作响。墙上镂空雕绘着无数佛陀们的坐像。一个个形态
维肖。楼内高悬者一个大鼓，鼓身上绘有佛祖释迦牟尼于菩提树下说
法的彩绘。
LONG);
	set("exits", ([
		"west" : __DIR__"road1",
                "south"  : __DIR__"zt",
                "north"  : __DIR__"yaoshidian",
	]));
	set("coor/x",-340);
  set("coor/y",-340);
   set("coor/z",30);
   setup();
}





