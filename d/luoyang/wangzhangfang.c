//  Room:  /d/luoyang/wangzhangfang.c

inherit  ROOM;

void  create  ()
{
        set("short",  "帐房");
        set("long",  @LONG
这里是王家的账房。满四壁都是帐簿架，堆满了陈年老帐，更有一
些帐簿堆在地下。一个师爷一脸酒气，正在收拾破烂帐。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south"  :  __DIR__"wangxiangfang",
                "east"   :  __DIR__"wangdatang",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/yi" : 1,
        ]));
	set("coor/x", -7031);
	set("coor/y", 2159);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}