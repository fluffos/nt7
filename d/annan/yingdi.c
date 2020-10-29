#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","军营");
  set ("long", @LONG
这里是安南的驻军大营。这里几乎都是官兵，一队官兵正在那里操
练，傍边有一个军官摸样的在那里指手画脚，好象是官军的头子。
你在这里十分的碍眼，你匆匆的走来
LONG);

  set("exits", ([ 

  "south":__DIR__"yingmen",
       ]));
set("objects",([
          __DIR__"npc/bing":5,
          __DIR__"npc/daxiang":2,
          ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
