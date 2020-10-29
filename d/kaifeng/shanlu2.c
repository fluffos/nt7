inherit ROOM;

void create ()
{
        set ("short", "山路");
        set("long", @LONG
这是一条黄土飞扬的山路，因为离嵩山等几处山脉还比较远，所
以它很是宽阔，路上来往人很多，路边相隔不远就有个小亭子供行人
歇脚，北边不远便是嵩山入口。
LONG );

        set("outdoors", "kaifeng");
        set("exits", ([
                "north" : "/d/songshan/taishique",
                "east" : "/d/shaolin/maowu",
                "eastup" : __DIR__"shanlu1",
        ]));

	set("coor/x", -5080);
	set("coor/y", 2270);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}