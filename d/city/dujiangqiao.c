// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short","渡江桥");
        set("long",@LONG
一座三拱石桥横卧在大运河上，桥的侧栏上由知州欧阳修题着「渡
江桥」，桥下各色船只穿流不息。东边是扬州最大的码头，漕运的粮食，
两淮产的盐，多在此装卸。过了桥就是扬州的南门。
LONG );
        set("outdoors", "yangzhou");
        set("region", "yangzhou_zone");

        set("exits", ([
                "north"  : __DIR__"nanmen",
                "south"  : "/d/wudang/wdroad1",
                "west"  : __DIR__"shulin1",
                "east"  : __DIR__"matou",
        ]));
        set("objects", ([
                CLASS_D("lingxiao") + "/shipopo" : 1,
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));
	set("coor/x", 0);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
