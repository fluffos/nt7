// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create ()
{
        set ("short", "大门");
        set ("long", @LONG
走到这里，一座富丽堂皇的大宅院出现在你的眼前，两头高大的
石狮子镇住了大门两侧，朱漆大门足足有三寸厚。门上挂着两个灯笼，
写着「荆州万府」四个金漆大字。只见两个衣衫华丽的青年站在大门
两侧，警惕地注视着行人。
LONG);
        set("outdoors", "jingzhou");
        set("region", "jingzhou");
        set("exits", ([
                "north"  : __DIR__"wan_dating",
                "south"  : __DIR__"xidajie1",
        ]));

        set("objects", ([
                "/d/shaolin/npc/shang2" : 2,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -7110);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if( dir == "north" &&
           objectp(present("jia ding", environment(me))) )
                return notify_fail(CYN "家丁拦住你骂道：什么东西，居然连万"
                                   "老爷的府邸都敢乱闯！\n" NOR);
        return ::valid_leave(me, dir);
}