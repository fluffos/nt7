#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",GRN"安南南门"NOR);
  set ("long", @LONG
这里是安南的南门。这里的行人不少。这里有几个官兵正在检查来
往的百姓。旁边有一个军官耀武扬威地站在那里，不停地指手画脚。
LONG);

  set("exits", ([ 

  "north":__DIR__"suishilu2",
  "south":__DIR__"tulu1",
       ]));
  set("objects",([
          __DIR__"npc/bing":2,
          ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
