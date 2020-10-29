inherit ROOM;

void create()
{
        set("short", "小茅房");
        set("long", @LONG
在空地上搭起的一个小茅房。连遮挡的门都没有。就在平地上挖
了个大坑，上面铺上两块木板。嗡嗡的苍蝇围着你乱转。一股臭味熏
得人直想逃出去，北面是片菜地，东面是个粪窖。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"caidi5",
                  "east" : __DIR__"fenjiao",
        ]));

	set("coor/x", -4990);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}