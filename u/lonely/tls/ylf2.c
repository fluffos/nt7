#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"应乐峰北"NOR);
        set("long", @LONG
南面便是点苍山最高峰应乐峰，山峰直插云霞，雄伟壮丽。这里天高
气寒，山顶还有终年不化的积雪。远远望去，宛如白色峨冠，这就是有名
的“苍山雪景”。
LONG);
        set("outdoors", "dali");

        set("exits", ([             
             "southup" : __DIR__"ylf",
               "north" : __DIR__"shanlu",
        ]));
set("objects", ([
	      "/d/dali/npc/huanglu" : 1,
          "/d/dali/npc/pig" : 1,
	]));

        set("coor/x",-350);
  set("coor/y",-380);
   set("coor/z",20);
   setup();
}