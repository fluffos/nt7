#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","兵器店");
  set ("long", @LONG
这里是家兵器店。由于现在处于战乱时期，所以这里生意很好。只
见铁匠正在敲敲打打。旁边地上的角落里堆满了各种兵器和护甲。只听
乒乓声中，又一件兵器打造好了。
LONG);

  set("exits", ([ 

  "west":__DIR__"suishilu2",
     ]));
 
  set("objects",([
          __DIR__"npc/tiejiang":1,
          ]));  
  
  set("valid_startroom", 1);
  setup();
 
}
