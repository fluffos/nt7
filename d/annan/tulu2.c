#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
这里是安南城南的一条小路，因为不是主要的驿道，道路的状况非
常不好，只是由沙石铺成，路面颠簸不平，一阵风吹过，卷起漫天的沙
土。西边的密林中隐约的有一条小路.
LONG);

  set("exits", ([ 

  "north":__DIR__"tulu1",
  "southeast":__DIR__"tulu3",
//  "southwest":__DIR__"shulin3",  
       ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
