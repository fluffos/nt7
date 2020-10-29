#include <room.h>
inherit ROOM;

void create()
{
        set("short", "鸟市");
        set("long", @LONG
你一走到这里，便听见了许许由各种各样鸟儿轻脆的叫声编织成
的动听的梵籁。你可以看到很多京城里衣着华丽的公子哥儿在这里精
挑细选，一个个油头粉面，平时无事可作，就靠这些来打发着混日子。
LONG );
       set("exits", ([
                "east" : "/d/beijing/xi_1",
                "west" : "/d/beijing/majiu",
        ]));
        set("objects", ([
                "/d/beijing/npc/richman1" : 1,
                "/d/beijing/npc/shusheng2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}