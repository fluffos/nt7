// /u/qingyun/lsd/lsgu.c
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIY"灵蛇谷"NOR);
        set("long", @LONG
这里是岛里的一个山谷。山谷长着许多奇花异草，到处花香鸟语，
分外美丽，这里远离凡尘，你到了此处不禁疑为仙境。此岛虽然到处
有毒蛇出没但唯有此处不见毒物之踪影，也许此间主人长在此间修行
之果。
LONG );
	set("exits", ([ 
  		"southup" : __DIR__"shanguang",
                "north" : __DIR__"sfjiao",
	]));
/*
	set("objects",([
             CLASS_D("mingjiao") + "/dai" : 1,
	]));
*/
	set("outdoors","灵蛇岛");
	setup();
}
