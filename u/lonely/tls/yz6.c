#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", GRN"松树院"NOR);
        set("long", @LONG
这里一座遍植青竹的小院子，当中一条小路通往千寻宝塔，白石
地面打扫得非常干净，轻风吹过，只吹得竹叶随风飘动，发出沙沙的
声响，却带不起一丝灰尘。东西各有一条小道。
LONG);
        set("outdoors", "天龙寺");
        set("exits", ([                           
               "southup" : __DIR__"gfd",
               "north" : __DIR__"ta1",
               "east" : __DIR__"ytd",
               "west" : __DIR__"sjt",
        ]));
        set("coor/x",-350);
  set("coor/y",-310);
   set("coor/z",20);
   setup();
}