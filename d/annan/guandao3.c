#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","红河道");
  set ("long", @LONG
这里是条官路。因著名的红河因土质呈土红色得名。这里的行人来来
往往，有些热闹。南来北往的有很多车马，一派热闹的景象。不时有
飞驰快马从你身边跑过，吓得路上的百姓都朝两边闪去。
LONG);

  set("exits", ([ 

  "south":__DIR__"guandao2",
  "north":__DIR__"guandao4",
  "northwest":__DIR__"yingmen",
       ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
