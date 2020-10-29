#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",HIY"安南皇宫"NOR);
  set ("long", @LONG
安南皇宫采用了北京故宫的图纸，所以你会发现自己进入
了一个缩小版的北京故宫。内有紫禁城，紫禁城里又分为两部
分，前面有皇帝平处理政务的勤政殿，后面有皇帝居住的乾成
殿，皇后住的坤泰宫，皇太子居住的光明殿，其他后妃居住的
顺辉院等。皇城内还设有旗台、太和殿和祭祀历代皇帝的宫广
殿和庙宇。。
LONG);

  set("exits", ([ 
"east":__DIR__"suishilu2",        

       ]));
  set("objects",([
          __DIR__"npc/bing":4,
          ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
