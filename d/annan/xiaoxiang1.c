#include <ansi.h>
inherit ROOM;

void create ()
{
  set ("short","小巷");
  set ("long", @LONG
这里是条小巷。平时有很多地痞流氓聚集在这里。只见这里人声嘈
杂，赌博叫骂的声音不绝于耳。
LONG);

  set("exits", ([ 

  "north":__DIR__"dongjie1",
     ]));
 set("objects",([
         __DIR__"npc/liumang":1,
        __DIR__"npc/liumang2":1,
         ]));
set("outdoors","annan");
  set("valid_startroom", 1);
  setup();
 
}
