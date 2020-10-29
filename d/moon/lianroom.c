// ken 1999.12.9
#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{       object 	con, item;
	set("short", "练功场");
	set("long", @LONG
 这个练武场比起其他的要大了几倍，细纱铺成的场地在
阳光下熠熠生光。在场地旁边放着几个兵器架，兵器架上
插满了各式各样的武器。
LONG	);
	set("exits", ([ 
  "westup" : __DIR__"fgaden",
]));
        set("objects",([
			__DIR__"npc/guards1" : 4,
                        __DIR__"obj/jia" : 1,
       	]) );
	set("coor/x",-20);
	set("coor/y",1090);
	set("coor/z",30);
	setup();
}
