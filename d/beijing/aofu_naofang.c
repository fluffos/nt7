#include <room.h>
inherit ROOM;

void create()
{
        set("short", "鳌府牢房");
        set("long", @LONG
这是一个昏暗的房间，窗户都被钉死。地上放着皮鞭、木棍等刑
具，显然这是鳌狠私立公堂，审讯人犯的所在。一个书生被捆在墙上，
鲜血淋漓，遍体鳞伤。
LONG );
        set("exits", ([
                "south" :  "/d/beijing/aofu_houyuan",
        ]));
        set("objects", ([
                 "/d/beijing/npc/zhuangyu" : 1,
        ]));

	set("coor/x", -2820);
	set("coor/y", 7800);
	set("coor/z", 0);
	setup();
}