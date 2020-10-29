#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", GRN"青竹院"NOR);
        set("long", @LONG
这里一座遍植青竹的小院子，当中一条小路向北通往无相塔，白
石地面打扫得非常干净，轻风吹过，只吹得竹叶随风飘动，发出沙沙
的声响，却带不起一丝灰尘。
LONG);
        set("outdoors", "天龙寺");
        set("exits", ([                           
               "west" : __DIR__"men1",
               "east" : __DIR__"men3",
               "north" : __DIR__"ta2",
               "southwest"  : __DIR__"yaoshidian",
        ]));
        set("coor/x",-330);
  set("coor/y",-320);
   set("coor/z",30);
   setup();
}