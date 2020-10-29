// Room: /city/wudao2.c

#include <ansi.h>
inherit "/d/city/underlt";

void create()
{
        set("short", "武道场");
        set("long", @LONG
这里是三面环山，只有北面有条出口的一坪山间平地。山坡山阵
阵松涛哗哗作响，山脚下的平地绿草如茵，中间架起了个擂台，四周
一溜过去搭着凉棚，棚中桌椅杯盆俱全。这里是青年组的比武场地！
LONG );
        set("outdoors", "city");
        set("exits", ([
                "leitai"      : "/d/city/leitai2",
                "west"        : "/d/city/wudao4",
        ]));
        set("no_fight", 1);
        setup();

        init_here();
        replace_program("/d/city/underlt");
}
