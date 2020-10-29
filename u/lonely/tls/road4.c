#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"白石路"NOR);
        set("long", @LONG
这里是天龙寺后山僧人和俗家弟子作休之处，西边传来菜饭的香
气，东边是天龙寺的武器房。不少弟子来此挑选自己趁手的兵器。东
面是慈悲院，西边山上是斗母宫，北边是天龙僧人睡房。
LONG);
        set("outdoors", "天龙寺");
        set("exits", ([             
               "west" : __DIR__"dmg",
               "east" : __DIR__"cby",  
               "north" : __DIR__"sroom",                            
               "southdown" : __DIR__"yz3",                           
        ]));
        set("coor/x",-350);
  set("coor/y",-280);
   set("coor/z",30);
   setup();
}