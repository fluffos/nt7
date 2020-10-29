#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","安南酒馆");
  set ("long", @LONG
这里是一家酒馆，看起来生意非常好，店小二跑来跑去，忙个不停
。几个酒客正在那里喝酒畅谈。门口飘扬着一面大旗，上面写着「安南
酒馆」四个大字，迎风飘扬，似乎在招呼着南来北往的客人。
LONG);

  set("exits", ([ 

  "southeast":__DIR__"xijie1",
      ]));
 
  set("objects",([
          __DIR__"npc/xiaoer":1,
          ]));
  set("valid_startroom", 1);
  setup();
 
}
