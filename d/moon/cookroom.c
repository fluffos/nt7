// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "厨房");
	set("long", @LONG
这里自从山庄建立时起，就一直没有闲来过，由于来访的宾客很
多，所有的人都一生不吭的忙碌着。灶上放着一笼刚蒸好的珍珠
蟹黄包和一碗热气腾腾的茯苓燕窝汤。
LONG	);
	set("exits", ([ 
  "eastup" : __DIR__"fgaden",
]));
        set("objects",([
			__DIR__"npc/cook" : 1,
       	]) );
	set("coor/x",-40);
	set("coor/y",1090);
	set("coor/z",30);
	setup();
}
