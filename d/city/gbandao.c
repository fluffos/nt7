// gbandao.c 练功房
// by aji
#include <room.h>

inherit ROOM;

void kick();

void create()
{
        set("short", "暗道");
        set("long", @LONG
一条狭窄的地下秘密通道，笔直的朝东面延伸。通道的尽头有明
亮的光线透进来。
LONG );
        set("exits", ([
		"east" : "/d/city/gbxiaowu",
                "out" : "/d/city/pomiao",
        ]));
	set("objects",([
		CLASS_D("gaibang") + "/jian" : 1
	]));
//	set("no_clean_up", 0);
	create_door("out", "小门", "enter", DOOR_CLOSED);

	set("coor/x", 40);
	set("coor/y", 40);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((!myfam || myfam["family_name"] != "丐帮") && dir == "east" &&
                objectp(present("jian zhanglao", environment(me))))
                return notify_fail("简长老一把揪住你的衣领说：“慢着！”\n");
        return ::valid_leave(me, dir);
}
