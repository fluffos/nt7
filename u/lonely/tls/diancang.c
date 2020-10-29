#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"点苍山"NOR);
        set("long", @LONG
点苍山俗称苍山，又叫灵鹫山。南诏时封为中岳山，北起洱源、邓川，
南至下关天生桥，东临洱海，西接漾濞，全长五十多公里。点苍山有十九座
山峰，峰峰相连，险峻峥嵘。每两座山峰之间夹一条溪水，共有溪水十八条，
条条清碧。十九座山峰，海拔都在三千米以上，最高的达四千一百多米，山
顶有终年不化的积雪。远远望去，宛如白色峨冠，这就是有名的“苍山雪景”
LONG);
        set("outdoors", "大理");
        set("exits", ([
              "eastup" : __DIR__"dc3",
              "westup" : __DIR__"dc3",
             "northup" : __DIR__"dc3",
           "southwest" : "/d/dali/daliwest/nj",
            "eastdown" : "/d/dali/ximen",
        ]));
        set("coor/x",-350);
  set("coor/y",-420);
   set("coor/z",-10);
   setup();
}

void init()
{
	object me = this_player();

	if(me->query_temp("xuncheng")) me->set_temp("dali_xc/18x",1);
}

