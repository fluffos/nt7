inherit ROOM;

void create()
{
        set("short", "稻香居");
        set("long", @LONG
稻香居有三百年的历史了。从这栋楼外面黑黑的招牌旗就能看出
来。不过里面的食客还是挺多。桌子坐满了人。楼上当然有雅座，不
过是要有一定身份地位的人才能上。
LONG );
        set("exits", ([
                "up" : __DIR__"daoxiang2",
                "west" : __DIR__"road2",
                "east" : __DIR__"majiu",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));

	set("coor/x", -5040);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}