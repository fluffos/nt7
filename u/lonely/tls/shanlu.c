#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这是条应乐峰以北山脚下的山路，路面用青砖铺成，每隔四五步又有
一匹由汉白玉制长砖，看来着实花了不少功夫。前面有一片斑竹林子，遥
现红墙和三座高塔，随风隐隐传来一阵寺院的钟声和佛门檀香香味。
LONG);
        set("outdoors", "dali");

        set("exits", ([             
               "south" : __DIR__"ylf2",
               "north" : __DIR__"gate",
        ]));
set("objects",([
                __DIR__"npc/duan-m" : 2,
        ]));

        set("coor/x",-350);
  set("coor/y",-370);
   set("coor/z",20);
   setup();
}