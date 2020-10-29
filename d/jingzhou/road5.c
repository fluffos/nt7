#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "青山");
        set("long", @LONG
山中树木茂密，花开万朵，倾耳细听，可以听见山溪流水的声音，
风吹树页的声音，如同一首大自然的乐曲，美妙动听。
LONG );
        set("exits", ([
                  "northeast" : __DIR__"qingshan1",
                  "west" : __DIR__"road6",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("coor/x", -370);
        set("coor/y", -200);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
