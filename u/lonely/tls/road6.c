#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"白石阶"NOR);
        set("long", @LONG
这里是依山而建的一段石阶路，是用点苍山特有的白石砌成，
路很陡很险。左面就是悬崖，一阵大风吹来，你不由的晃了几晃，
吓出一身冷汗。
LONG);
        set("outdoors", "天龙寺");
        set("exits", ([             
               "southdown" : __DIR__"dmg",               
        ]));
        set("coor/x",-360);
  set("coor/y",-270);
   set("coor/z",30);
   setup();
}