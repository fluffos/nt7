// Room: /city/zxlpath.c
// YZC 1995/12/04 

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "醉仙楼大堂");
        set("long", @LONG
这是醉仙楼大堂，来来往往的客人和跑堂小二，夹杂着三个宴会
厅刺耳的呼叫声，碰杯声，打闹声，赖酒声，热闹非凡。你在三个宴
会厅前打量着进哪个凑个热闹，蹭点白食。    东边是玫瑰厅，朝南
的是牡丹厅，向北是芙蓉厅。
LONG );
	set("exits", ([
		"east"   : "/d/city/meigui",
		"north"  : "/d/city/furong",
		"south"  : "/d/city/mudan",
		"west"   : "/d/city/zuixianlou2",
	]));
        set("no_fight","1");
	set("no_clean_up", 0);
	set("coor/x", 20);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
