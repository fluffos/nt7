#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"白石路"NOR);
        set("long", @LONG
这里又是一段白石路，连接着前面的大雄宝殿后后面的天王殿，
石面平滑，打扫得干干净净。抬眼一看，雪峦万仞，镂银洒翠的点苍
山峙其后，波涛万顷、横练蓄黛的洱海嵌于前。寺内三塔鼎峙，撑天
拄地；玉柱标空，雄浑壮丽，为苍洱间的胜景之一。
LONG);
        set("outdoors", "dali");

        set("exits", ([             
               "southup" : __DIR__"twd",
               "northup" : __DIR__"baodian",     
               "east" : __DIR__"gulou",
               "west" : __DIR__"zhonglou",

        ]));
        set("objects",([
                __DIR__"npc/guest" : 1,
				 __DIR__"npc/xin-qing" : 1,
        ]));


        set("coor/x",-350);
  set("coor/y",-340);
   set("coor/z",20);
   setup();
}