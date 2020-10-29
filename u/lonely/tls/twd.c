#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"天王殿"NOR);
        set("long", @LONG
穿过前院一段白石小路，登上七层石阶，便是天王殿。殿内两侧
分立四大伏魔金刚，正中贡案上两盏长明灯吐着雄雄火焰，一座尺余
高的铁鼎中香烟缭绕。东西两边是寺院的斋堂。
LONG);
        set("exits", ([             
               "southdown" : __DIR__"road",
               "northdown" : __DIR__"road1",                             
        ]));
        set("coor/x",-350);
  set("coor/y",-350);
   set("coor/z",30);
   setup();
}