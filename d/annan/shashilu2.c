#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
这里是条沙石路。这里地势一片空阔，四处望去一片平坦。不时有
鸟儿从你的头上飞过。这里没有什么人，你不禁加快了行进的脚步。
LONG);

  set("exits", ([ 

  "northwest":__DIR__"shashilu1",
  "southwest":__DIR__"qiuling6",
 // "west":__DIR__"hg",
       ]));
 
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
