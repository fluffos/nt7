#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西单");
        set("long", @LONG
这里就是西单，西单也是京城里的繁华地段。人来人往，十分热
闹。游人虽然多，但大都只四处晃悠，着东瞅瞅西看看，也不急着买
什么。从右边飘来一阵浓浓的药材气味，那里就是著名的『回春堂』
药铺了。不断有人从北边走来，似乎那里也挺热闹。南边则是京城里
的西长安大街。
LONG );
       set("exits", ([
                "east" : "/d/beijing/huichuntang",
                "west" : "/d/beijing/xi_1",
                "north" : "/d/beijing/bei_2",
                "south" : "/d/beijing/caroad_w2",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy3" : 1,
                "/d/beijing/npc/xiaofan" : 1,
                "/d/beijing/npc/girl2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}