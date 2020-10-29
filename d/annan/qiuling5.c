#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","丘陵");
  set ("long", @LONG
这里是安南城南的一片丘陵地，丘陵起伏不平，红褐色的岩石奇型
怪状，沙石路到这里逐渐隐没于丘陵之中，因为这附近有强人出没，行
人几乎都不到这里来。
LONG);

  set("exits", ([ 

  "west":__DIR__"qiuling2",
  "northeast":__DIR__"qiuling6",
       ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
