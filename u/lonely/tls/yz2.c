#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", GRN"斑竹院"NOR);
        set("long", @LONG
这里是石路旁的一座小院子，院内遍植湘妃斑竹，轻风吹过，竹
干随风飘动，发出沙沙的声响。一旁摆有几只石凳，是准备给进香客
们歇脚用的。
LONG);
        set("outdoors", "天龙寺");
        set("exits", ([                           
               "north" : __DIR__"zt",
               "west" : __DIR__"road",
        ]));
        set("coor/x",-340);
  set("coor/y",-360);
   set("coor/z",30);
   setup();
}
