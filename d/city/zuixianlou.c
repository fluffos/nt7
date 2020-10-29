// Room: /city/zuixianlou.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "醉仙楼");
        set("long", @LONG
方圆数百里内提起醉仙楼可以说是无人不知，无人不晓。当年苏
学士云游到此，对醉仙楼的花雕酒赞不绝口，欣然为其题匾，流下一
段传遍海内的佳话，从此醉仙楼名声大震。楼下布置简易，顾客多是
匆匆的行人，买点包子、鸡腿、米酒就赶路去了。楼上是雅座。
LONG );
	set("exits", ([
		"west" : "/d/city/beidajie2",
		"up" : "/d/city/zuixianlou2",
	]));
	set("objects", ([
		"/d/city/npc/xiaoer2" : 1,
        "/adm/npc/kuangfeng" : 1,
	]));
        set("no_fight", 1);
	set("coor/x", 10);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}