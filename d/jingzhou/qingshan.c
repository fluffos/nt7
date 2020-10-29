#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山顶");
        set("long", @LONG
爬上山顶，只觉空气清新，登高望远，心旷神怡。向东望去，只
见扬洲城有如一个小小的黑点，极目向西，却茫茫而不见。南面，只
见一条大江如彩带一般，那就是长江了。
LONG );
        set("exits", ([
                //"eastdown" : __DIR__"qingshan2",
                "north" : __DIR__"gumiao",
                "westdown" : __DIR__"qingshan1",
                "southdown" :__DIR__"chibi1"
        ]));
        set("objects", ([
                "/d/beijing/npc/youke" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("coor/x", -350);
        set("coor/y", -190);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
