// Room: /city/bingyindamen.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "兵营大门");
        set("long", @LONG
你正站在兵营的门口，面对着一排简陋的营房，可以看到穿着制
服的官兵正在操练，不时地传来呐喊声。老百姓是不允许在此观看的，
你最好赶快走开。
LONG );
	set("exits", ([
		"south" : "/d/city/bingyin",
		"north" : "/d/city/xidajie1",
	]));
	set("objects", ([
		"/d/city/npc/bing" : 2,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -10);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
	if (!wizardp(me) && objectp(present("guan bing", environment(me))) && 
		dir == "south")
		return notify_fail("官兵拦住了你的去路。\n");
	return ::valid_leave(me, dir);
}