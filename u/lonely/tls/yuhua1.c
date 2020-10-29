#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", MAG"雨花阁"NOR);
        set("long",@LONG
雨花阁是寺中三阁之一，为藏经存书之处。四壁靠墙都立满了竹
架，架上经书文献不计其数。因天龙寺乃是帝王出家之地，每到节日
必有世俗子弟到寺中朝拜，每朝拜一次，必有奉献装修。北面有个小
门通向寺院后面的松林。
LONG);
        set("exits", ([
                "out" : __DIR__"yuhua",
                "north" : __DIR__"road7",

	]));

        set("objects",([
                __DIR__"npc/liao-si" : 1,
    //            __DIR__"obj/fojing2"+random(2) : 1
        ]));

        setup();
}
