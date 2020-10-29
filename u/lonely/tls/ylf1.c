#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"应乐峰南"NOR);
        set("long", @LONG
北面便是点苍山最高峰应乐峰，山峰直插云霞，雄伟壮丽。这里天高
气寒，山顶还有终年不化的积雪。远远望去，宛如白色峨冠，这就是有名
的“苍山雪景”。
LONG);
        set("outdoors", "dali");

        set("exits", ([             
             "northup" : __DIR__"ylf",
                "south": __DIR__"dc1",
        ]));

        set("coor/x",-350);
  set("coor/y",-400);
   set("coor/z",20);
   setup();
}
void init()
{
            object me = this_player();
     if(me->query_temp("xuncheng"))
     {
       me->set_temp("dali_xc/ylf1",1);
      }
}


