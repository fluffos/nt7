// Room:/d/changan/tulu2.c

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
这是一条黄土飞扬的路，不算太宽，南边远远望过去可以看得到
巍峨的长安城墙，虽然这里离长安并不远，但是经常会受到北方的游
牧民族的骚扰，因此人烟并不茂盛。
LONG );
        set("exits",  ([  /*  sizeof()  ==  2  */
                "northeast": "/d/changan/tulu2",
                "south"    : "/d/changan/bei-chengmen",
        ]));
        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}