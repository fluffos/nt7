#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "大海");
        set("long", @LONG
这里是一望无际的大海；
LONG);

        set("no_flyto", 1);
        set("outdoors", "dahai");
        set("no_clean_up", 1);
        setup();

}