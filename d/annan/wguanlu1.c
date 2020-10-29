#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","官路");
  set ("long", @LONG
这里是条官路。东边是安南的西门。这里的行人来来往往，有些热
闹。有很多车马朝东边走去，一派热闹的景象。不时有大队的官兵
从你的身旁走过，吓得路上的百姓都朝两边闪去。
LONG);

  set("exits", ([ 

  "east":__DIR__"ximen",
  "southwest":__DIR__"shalu1",
       ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
