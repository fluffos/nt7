// /u/qingyun/lsd/sfjiao.c
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", GRN"山峰脚下"NOR);
        set("long", @LONG
这里四周长着许多长草，此岛名为『灵蛇岛』，岛上定然长虫特
多，不时会有毒虫窜出。在这里你只能尽往光秃的山石处落脚。往南
而上是山峰顶部，依稀可见一座茅屋座落其中。
LONG );
	set("exits", ([ 
  		"south" : __DIR__"lsgu",
  		"northup" : __DIR__"shanfeng",
	]));
	set("objects",([
            "/clone/beast/snake"  :       1,
	]));
	set("outdoors","灵蛇岛");
	setup();
}
