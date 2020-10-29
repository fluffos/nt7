#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","安南中央广场");
  set ("long", @LONG
漫步安南，新老建筑交相辉映，安南人不分老幼都有爱嚼槟榔的
习惯嘴里总是红红的，安南少女爱穿红色的筒裙，而那些戴着大斗笠
的妇女大都是郊区妇女，她们出门必戴斗笠，既能遮阳又能挡雨。 
LONG);

  set("exits", ([ 
"west":__DIR__"gj1",
"east":__DIR__"gj2",        
  "southwest":__DIR__"xijie1",
  "southeast":__DIR__"dongjie1",
  "north":__DIR__"qingshilu1",
       ]));
 set("objects",([
         __DIR__"npc/bing2":1,
         __DIR__"npc/bldizi":1,
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
