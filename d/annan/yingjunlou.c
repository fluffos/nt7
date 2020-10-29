#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","迎君楼");
  set ("long", @LONG
这里是安南最大的春楼--“迎君楼”。门口有几个姑娘在招呼来往
的行人。抬头望去，这座楼足有三层之高，每层楼上都传来调笑的声音。
「迎君楼」大招牌挂在最上面，似乎比王府贵族还要气派。不时有安南
帮的弟子从这里出出入入。
LONG);

  set("exits", ([ 

  "west":__DIR__"qingshilu1",
       ]));
 set("objects",([
         __DIR__"npc/xiaocui":1,
         ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
