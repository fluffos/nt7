#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
这里是条沙石路。一阵风吹过，卷起漫天的沙土。不时有人骑马从
你身旁驰过。
LONG);

  set("exits", ([ 

  "northeast":__DIR__"wguanlu1",
  "southwest":__DIR__"shalu2",
       ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
