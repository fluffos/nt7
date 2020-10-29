#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "【太虚】" NOR);
        set("long", HIW @LONG

                 太              虚

    这里是三界之外的太虚之中，四周白茫茫的一片，不见任何事物。

LONG NOR );

        set("sleep_room", 1);

        set("sky", 1);
        // 在此演练阴阳九转十二重天
        set("yinyang", 1);
                set("valid_startroom", 1);
        setup();
}
