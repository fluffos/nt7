#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小溪");
  set ("long", @LONG
这里是条小溪。溪水清澈见底，还有几条鱼在游来游去。这里风景
秀丽，山水如画，空气清新。地上有很多漂亮的野花、蒲公英等植物。
不时有野兔从你的脚旁跳过。
LONG);

  set("exits", ([ 

  "east":__DIR__"shulin1",
    ]));
  set("objects",([
          __DIR__"npc/she":2,
          ]));
  set("resource/water",1);
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
