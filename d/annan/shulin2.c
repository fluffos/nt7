#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","热带雨林");
  set ("long", @LONG
这里是一片一望无垠林海，每棵树木都有十来丈高，周围阡陌交错，
几十丈高的大树簇在一块，密实的枝叶象一蓬蓬巨伞般伸向天空，把阳
光遮得丝毫也无。你侧耳倾听，似乎有溪水流动的声音。
LONG);

  set("exits", ([ 
  "north":__DIR__"shulin1",
  "south":__DIR__"shulin2",

  "northeast":__DIR__"shulin1",
  "west":__DIR__"lu1",
  "southeast":__DIR__"shulin9",
    ]));

 set("objects",([
         __DIR__"npc/dushe":2,        
         ]));  
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
