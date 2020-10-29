// /d/gaoli/xuanwumen
#include <ansi.h>


inherit ROOM;


void create()
{
        set("short", "浑江口");
        set("long", @LONG
浑江口西岸也是相当热闹，自西岸渡口往西，一条笔直的土路直通
山海关。此地民风淳朴，路旁夹柳成阴，酒厮林立，且都有一面大大的
「酒」旗迎风飘扬，蔚为壮观。也有不少小贩沿路叫买，语多难辨，却
也令人盛情难却。
LONG
        );

        set("exits", ([
                "west" : __DIR__"dadao1",
                "southwest" : __DIR__"yucun",
                "east" : __DIR__"jiangdong",

        ]));

        set("outdoors", "/d/gaoli/hunjiangkou");
        setup();
}

