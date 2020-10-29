#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", GRN"松树院"NOR);
        set("long", @LONG
这里是石路旁的一座小院子，松树成荫，地上撒满了飘落的松针。
一旁摆有几只石凳，是准备给进香客们歇脚用的。
LONG);
        set("outdoors", "天龙寺");
        set("exits", ([                           
               "north" : __DIR__"zt1",
               "east" : __DIR__"road",
        ]));
        set("coor/x",-360);
  set("coor/y",-360);
   set("coor/z",20);
   setup();
}
