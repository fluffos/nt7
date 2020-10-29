inherit ROOM;

void create()
{
  set("short","松树林");
  set("long",@LONG
这里是一片茂密的松树林，松树高大，枝叶茂盛，你一走进来差
点便迷失了方向。这里灌木丛生，路都给挡住了。
LONG);

     set("outdoors", "天龙寺");
     set("exits",([
           "east" : __DIR__"songlin-2",
           "west" : __DIR__"songlin-4",
           "north" : __DIR__"songlin-3",
           "south" : __DIR__"songlin-1",
     ]));
    
     set("coor/x",-310);
  set("coor/y",-290);
   set("coor/z",40);
   setup();
}
#include "songlin.h"