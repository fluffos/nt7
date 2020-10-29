#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"白石路"NOR);
        set("long", @LONG
这里又是一段白石路，石面平滑，打扫得干干净净。路旁种有各
式花草，两株参天大树分立左右两边。北面是无无境，往南是般若台、
清都瑶台等地。
LONG);
        set("outdoors", "天龙寺");
        set("exits", ([             
               "north" : __DIR__"wwj",
               "southdown" : __DIR__"yaotai",
   	       "southeast" : __DIR__"banruo",            
        ]));
        set("coor/x",-310);
  set("coor/y",-310);
   set("coor/z",40);
   setup();
}
