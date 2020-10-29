#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",GRN"安南西门"NOR);
  set ("long", @LONG
这里是安南的西门。这里的行人不少。这里有几个官兵正在检查来
往的百姓。旁边有个官兵耀武扬威地站在那里，不停地在那里指手画脚。
LONG);

  set("exits", ([ 

  "east":__DIR__"xijie2",
  "west":__DIR__"wguanlu1",
       ]));
  set("objects",([
          __DIR__"npc/bing":2,
          ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
