#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小路");
  set ("long", @LONG
你正走在一条崎岖不平的山路上，偶尔听到一阵阵的野兽叫声，头
顶有一些不知名的小鸟在跳来跳去，四周丛林密布，鲜花绿草若隐若现，
随着山谷里吹来的阵阵清风，传来哗哗的松涛声和一些淡淡的花香。
LONG);

  set("exits", ([ 

  "east":__DIR__"shulin2",
//  "southwest":"/d/xiangyang/shalu3",
    ]));
  
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
