#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", GRN"青竹院"NOR);
        set("long", @LONG
这里一座遍植青竹的小院子，当中一条小路通往后山上，白石地
面打扫得非常干净，轻风吹过，只吹得竹叶随风飘动，发出沙沙的声
响，却带不起一丝灰尘。东西各有一条小道。
LONG);
        set("outdoors", "天龙寺");
        set("exits", ([                           
               "south" : __DIR__"ta1",
               "northup" : __DIR__"road4",
               "west" : __DIR__"gmd",
               "east" : __DIR__"xmd",
        ]));
        set("coor/x",-350);
  set("coor/y",-290);
   set("coor/z",20);
   setup();
}