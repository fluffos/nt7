// Room:/d/changan/tulu4.c

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
这是一条黄土飞扬的路，不算太宽，路上的行人也不多，大概是
地处偏远的缘故，几乎没有什么人烟。
LONG );
        set("exits",  ([  /*  sizeof()  ==  2  */
                "southwest" : "/d/changan/tulu3",
        ]));
        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 2020);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}