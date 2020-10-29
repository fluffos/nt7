#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","沙石路");
  set ("long", @LONG
这里是条沙石路，一阵风吹过，卷起漫天黄沙。这里地势一片空阔，
四处望去一片平坦。不时有鸟儿从你的头上飞过。
LONG);

  set("exits", ([ 

  "northwest":__DIR__"xiaolu2",
  "southeast":__DIR__"shashilu2",
       ]));
 
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
