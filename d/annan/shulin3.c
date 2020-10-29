#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","红河");
  set ("long", @LONG
红河发源于中国云南省巍山县，在中国境内称为元江，全长1200公里，
在中国云南境内长695公里在安南境内长505公里,红河和湄公河水力
资源丰富。海岸线长3260千米，沿岸多天然良港。
LONG);

  set("exits", ([ 
  "north":__DIR__"shulin1",
  "south":__DIR__"matou",

  //"northeast":__DIR__"tulu2",
  "northwest":__DIR__"shulin4",
    ]));
   set("objects",([
         __DIR__"npc/daxiang":1,
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
