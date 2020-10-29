inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
这是衙门大堂后面的走廊，走廊西面有一小石拱门，里面
是一个小花园，花丛中有两个花匠正在修剪花草。北面走廊的
尽头的门开着，不知是不是就是师爷处。
LONG);
        set("exits", ([
                "south" : __DIR__"zoulang",
                "north" : __DIR__"shiye",
                 
        ]));

        set("coor/x", -9060);
	set("coor/y", -960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}