// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "破祠堂");
        set ("long", @LONG
这是一个破败的祠堂。地下满是灰尘，桌椅都是甚是残破。
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "west" : __DIR__"wan_huayuan",
        ]));
        set("objects", ([
                __DIR__"npc/taohong" : 1,
        ]));

        set("coor/x", -7100);
	set("coor/y", -2000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}