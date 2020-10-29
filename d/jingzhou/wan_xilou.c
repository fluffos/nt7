// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "西楼");
        set ("long", @LONG
这是万老爷子住的地方。摆设简单整洁，右首一张木床。方砖地上
有几处凹凸，显是主人勤于习武所致。
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "north" : __DIR__"wan_shufang",
                "east"  : __DIR__"wan_dating",
        ]));

        set("no_clean_up", 0);
        set("coor/x", -7120);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}