// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "走廊");
        set ("long", @LONG
这是一条长长的走廊。走廊西边是万府大厅。东边的尽头是个小客堂。
LONG);
        set("region", "jingzhou");
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/qifang" : 1,
        ]));
        set("exits", ([
                "south"  : __DIR__"wan_dating",
                "north"  : __DIR__"wan_ketang",
        ]));

        set("coor/x", -7110);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (!objectp(present("hu cheng", me)) &&
                dir == "north" &&
                objectp(present("qi fang", environment(me))))
                return notify_fail("戚芳拦住你说：我夫君中毒卧床，请勿打扰。\n");

        return ::valid_leave(me, dir);
}