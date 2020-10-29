#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","红河道");
  set ("long", @LONG
这里是条官路。因著名的红河因土质呈土红色得名。南边是安南的北门。
这里的行人来来往往，有些热闹。南来北往的有很多车马，一派热闹
的景象。
LONG);

  set("exits", ([ 

  "south":__DIR__"guandao3",
  "north":__DIR__"matou",
       ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
