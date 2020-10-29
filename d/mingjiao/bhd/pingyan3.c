// pingyan3.c 绿野
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", GRN"绿野"NOR);
        set("long", @LONG
这里是岛屿的东部。极目的是一片看不到尽头的大绿野，是活火
山经几千万年的火山灰堆积而成，平野上一群梅花鹿正在低头吃草，
周围一片平静，绝无可怖之处，远处高山处玄冰白雪，些处却是极目
青绿，苍松翠柏，更诸般奇花异树，皆为中土所无。
LONG );
	set("exits",([
		"north" : __DIR__"pingyan1",
                "south" : __DIR__"pingyan2",
                "west" : __DIR__"pingyan3",
		"east" : __DIR__"pingyan4",
	]));
	set("objects",([
		"/d/mingjiao/npc/lu" :  1,
	]));
	set("outdoors","冰火岛");
	setup();
}

void init()
{
      string a,b,c,d;
      a =query("exits/west");
      b =query("exits/north");
      c =query("exits/east");
      d =query("exits/south");
       set("exits/north", a);
       set("exits/west", b);
       set("exits/south", c);
       set("exits/east", d);
}
