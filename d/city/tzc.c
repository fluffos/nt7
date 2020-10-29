#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY+BLINK"挑战擂台"NOR);
        set("long", @LONG
[1；36m这里是专门设来接受外国挑战的擂台。
LONG );
        set("no_drift", 1);
        set("no_clean_up", 0);
        set("exits",([
                "down" : "/d/city/guangchang",
        ]));

        setup();
        replace_program(ROOM);
}
