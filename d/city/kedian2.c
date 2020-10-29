// Room: /city/kedian2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "客店二楼");
        set("long", @LONG
你正走在客店二楼的走廊上，可以听到从客房里不时地呼呼的打
酣声，一阵高过一阵。不时有睡意朦胧的旅客进进出出，到楼下的掌
柜处付了钱再上来睡觉。
LONG );
	set("exits", ([
		"down"  : "/d/city/kedian",
		"enter" : "/d/city/kedian3",
	]));

	set("objects", ([
                CLASS_D("shaolin") + "/xingzhe" : 1,
	]));
//	set("no_clean_up", 0);
	set("coor/x", 10);
	set("coor/y", 10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}