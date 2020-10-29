#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
这里是条沙石路。这里的行人很少。据说这里经常有强人出没，你
不禁小心起来。
LONG);

  set("exits", ([ 

  "northeast":__DIR__"shalu1",
  //"west":__DIR__"shulin1",
       ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
