#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","湄公河");
  set ("long", @LONG
湄公河发源于中国青藏高原，上游称澜沧江，经老挝、泰国、柬埔寨
流入安南南部，分为南北干流，北干流称前江，南干流称后江，最后
两条干流又分成九条支流入海，故又称九龙江。
LONG);

  set("exits", ([ 
  "south":__DIR__"shulin7",
  "northwest":"/d/lumaji/s_kou",

  "west":__DIR__"shulin2",
  "northeast":__DIR__"shulin7",
  "southeast":__DIR__"shulin8",
    ]));
   set("objects",([
         __DIR__"npc/daxiang":1,
         __DIR__"npc/tiger":1,        
         __DIR__"npc/dushe":2,        
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
