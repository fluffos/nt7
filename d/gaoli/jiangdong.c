// /d/gaoli/xuanwumen
#include <ansi.h>


inherit ROOM;


void create()
{
        set("short", "鸭绿江东岸");
        set("long", @LONG
面前是一条波涛翻滚的大江(river)。 浊流滚滚，万舟竞发。两岸
渡船来来往往，江边一长溜摆满了鱼摊，渔家就将船泊在岸边，几个破
萝上面支一块木板，板上摆满了活蹦乱跳的鲤鱼。不少过江客都在这里
等待渡船摆渡。
LONG
        );

        set("exits", ([
                "east" : __DIR__"dadao2",
                "west" : __DIR__"jiangkou",

        ]));



        set("outdoors", "/d/gaoli/edao2");
        setup();
}

