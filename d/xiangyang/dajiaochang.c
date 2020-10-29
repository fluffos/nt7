// Room: /d/xiangyang/daxiaochang.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "大校场");
        set("long", @LONG
这是襄阳守军用来校阅军士的地方。只见校场正中巍巍搭着一座
高台，台南排列着千余张椅子板凳。台前竖着两根旗杆，旗杆顶上有
着硕大的旗斗。校场里聚集着数百个四袋以上的丐帮弟子。他们都是
来竞选新任丐帮帮主的。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "north" : __DIR__"westjie3",
        ]));
        set("coor/x", -7850);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}