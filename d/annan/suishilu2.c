#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","碎石路");
  set ("long", @LONG
这里是条碎石路。南边就是安南的南门了。东边有一家兵器店，那
里传来敲敲打打的声音。那家兵器店以制作护具出名，很多武林人士都
到那里去买盔甲、盾牌等。
LONG);

  set("exits", ([ 

  "north":__DIR__"suishilu1",
  "south":__DIR__"nanmen",
  "east":__DIR__"bingqidian",
   "west":__DIR__"hg",
       ]));
 
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
