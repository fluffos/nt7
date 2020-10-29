#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", MAG"雨花院"NOR);
        set("long",@LONG
此处依山傍水，一条小溪从你眼前静静流过，一座精雕木桥横跨
其上，与其倒影恰成一圆，映着空灵的水面。溪旁遍植百花，风吹花
落，便有了雨花院之称。院内雨花阁精舍乃是寺中藏经存书之处，虽
有几个和尚来来去去，却不闻一丝声响。
LONG);
        set("outdoors","天龙寺");
        set("exits", ([
                "south" : __DIR__"wwj",
		"enter" : __DIR__"yuhua1",
                "east" : __DIR__"songlin2",
	]));
        set("coor/x",-310);
  set("coor/y",-290);
   set("coor/z",40);
   setup();
}
