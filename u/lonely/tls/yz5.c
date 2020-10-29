#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", GRN"青竹院"NOR);
        set("long", @LONG
这里一座遍植青竹的小院子，当中一条小路向北通往无住塔，白石地
面打扫得非常干净，轻风吹过，只吹得竹叶随风飘动，发出沙沙的声响，
却带不起一丝灰尘。
LONG);
        set("outdoors", "dali");

       set("exits", ([                           
               "east" : __DIR__"men2",
               "west" : __DIR__"men4",
               "north" : __DIR__"ta3",
               "southeast"  : __DIR__"dizangdian",
        ]));
set("objects",([
		__DIR__"npc/guest" : 2,
		__DIR__"npc/shami" : 1,
		]));
        set("coor/x",-370);
  set("coor/y",-320);
   set("coor/z",20);
   setup();
}