#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蜀道");
        set("long", @LONG
你走在以险著称天下的蜀道上，道路十分狭窄，这里不时会有强
盗出没，来往的人很少，举目看去，方圆几百里内没有人烟，你还是
加快步子走吧。
LONG );
        set("exits", ([
                  "east" : __DIR__"shudao11",
                  "west" : __DIR__"shudao13",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15090);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}