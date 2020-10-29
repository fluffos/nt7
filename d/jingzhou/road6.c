#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "小路");
        set("long", @LONG
这里是一条崎岖的黄土小路，路旁杂草丛生，西边只见黄土飞扬，
好象是条大官道。东面则有一座青山，山上树木茂密。
LONG );
        set("exits", ([
                  "east" : __DIR__"road5",
                  "west" : __DIR__"road7",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("coor/x", -380);
        set("coor/y", -200);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
