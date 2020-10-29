#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",GRN"安南东门"NOR);
  set ("long", @LONG
这里是安南的东门。这里的行人不少。这里有几个官兵正在检查来
往的百姓。旁边还有几个官兵在勒索想进城的百姓，有一个官兵还在旁
边指手画脚，一副神气的样子。
LONG);

  set("exits", ([ 

  "west":__DIR__"dongjie2",
  "east":__DIR__"xiaolu1",
       ]));
  set("objects",([
          __DIR__"npc/bing":2,
          ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
