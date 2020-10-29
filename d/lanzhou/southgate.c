//  Room:  /d/lanzhou/southgate.c

inherit  ROOM;

void  create  ()
{
        set("short",  "南门");
        set("long",  @LONG
这是兰州南门，城墙刚修整过显得气势雄伟。由于兰州是军事重镇，
因此官兵们都打起十二分精神检查来往行人。一条笔直的官道向南北两
边延伸。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"road2",
                "south" : __DIR__"road1",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                "/d/city/npc/wujiang": 1,
                "/d/city/npc/bing": 2,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "lanzhou");
	set("coor/x", -15750);
	set("coor/y", 3790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}