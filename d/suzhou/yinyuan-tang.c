// Room: /d/suzhou/yinyuan-tang.c    拜堂之处
// by llm 99/06

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "姻缘堂");
        set("long", @LONG
你简直走进了一片红色的世界，高低左右地垂着各式各样的红绸
绫缎彩纸贴花，细细看去，每一处竟都绣扎着鸳鸯凤凰，透出一股股
浓郁的喜庆气氛，当中一块横匾：          千里姻缘一线牵
LONG );
        set("exits", ([
                "west" : "/d/suzhou/hongniang-zhuang",
        ]) );
        set("objects", ([
        ]) );
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);
        set("no_sleep_room",1);

        set("coor/x", 240);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
