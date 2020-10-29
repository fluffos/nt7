// /d/mingjiao/lsd/shanguang.c
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", GRN"山岗"NOR);
        set("long", @LONG
只见山岗上稀稀落落长着一些花草和风棵不知名的树木，树木不
高，但却长得葱翠，山岗的另一侧是一座小石山。往西而下是岸边，
往东而下是山峰脚下。往北而下是灵蛇谷。
LONG );
	set("exits", ([ 
  		"westdown" : __DIR__"anbian",
		"northdown" : __DIR__"lsgu",
	]));
	set("outdoors","灵蛇岛");
	setup();
}
