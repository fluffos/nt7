// Room: /city/ymdongting.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "衙门正厅");
        set("long", @LONG
堂上东西有两根楹住，挂着一幅对联，但是你无心细看。正墙上
悬挂一个横匾，上书『正大光明』四个金光闪闪的大字。知府正坐在
文案后批阅文书，师爷随侍在后。
LONG );
	set("exits", ([
		"east"  : "/d/city/dongting",
		"west"  : "/d/city/xiting",
		"north" : "/d/city/neizhai",
		"south" : "/d/city/yamen",
	]));
	set("objects", ([
		"/d/city/npc/cheng" : 1,
		"/d/city/npc/shiye" : 1,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -10);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}