#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","西街");
  set ("long", @LONG
这里是安滹的西街。北面有一家酒馆，里面传来了阵阵的酒香。往
西走就可以到安南的西门了。只见几个喝醉的豪客正从酒馆中出来，摇
摇晃晃地朝西边走去了。
LONG);

  set("exits", ([ 

  "northeast":__DIR__"center",
  "west":__DIR__"xijie2",
  "northwest":__DIR__"jiuguan",
  "south":__DIR__"suishilu1",
       ]));
 set("objects",([
         __DIR__"npc/xiaojie":1,
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
