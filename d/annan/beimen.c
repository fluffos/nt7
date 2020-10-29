#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",GRN"安南北门"NOR);
  set ("long", @LONG
这里是安南的北门。这里的行人不少。这里有几个官兵正在检查来
往的百姓。有个军官耀武扬威地站在这里，不停地指手画脚。
LONG);

  set("exits", ([ 

  "south":__DIR__"qingshilu2",
  "north":__DIR__"guandao1",
       ]));
  set("objects",([
          __DIR__"npc/bing":2,
          ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
