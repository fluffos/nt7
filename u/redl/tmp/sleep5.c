// Room: /city/kedian3.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "休息室");
        set("long", @LONG
这是一间很大的客房，陈设十分简陋。靠墙放了十几张小木床，
不少客人正和衣而卧，满屋子都是呼呼的打酣声。西边有张床是空的，
你蹑手蹑脚地走了过去。
LONG );
	set("sleep_room", 1);
	set("no_fight", 1);
        set("hotel",1);
	set("no_clean_up", 0);
	set("exits", ([
		"out" : "/d/city/kedian2",
	]));
	set("coor/x", 9);
	set("coor/y", 9);
	set("coor/z", 9);
	setup();
}

int valid_leave(object me, string dir)
{
	if( dir == "out")delete_temp("rent_paid", me);

	return ::valid_leave(me, dir);
}
