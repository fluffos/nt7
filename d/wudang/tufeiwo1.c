#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "林中小路");
        set("long", @LONG
你走在一条僻静的林中小路上，两旁是阴森森的树林。只见左右
前后，到处都是铺天盖地的松树林。几十丈高的大松树簇在一块，密
实的枝叶象一蓬蓬巨伞恒伸向天空，把阳光遮得丝毫也无。据说这里
经常有土匪出没，不可久留。
LONG );
        set("outdoors", "sanbuguan");
        set("exits", ([
                "south"     : __DIR__"tufeiwo2",
                "northdown" : __DIR__"wdroad10",
        ]));
        set("objects", ([
                __DIR__"npc/tufei2" : 2
        ]));
        set("coor/x", -320);
        set("coor/y", -190);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
