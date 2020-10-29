inherit ROOM;

void create()
{
        set("short", "荆州西门" );
        set("long", @LONG
你来到荆州的西门，荆州历来都是军事要地，因此城墙坚实无比，
城楼高高耸立，出了西门，就踏上了艰险的蜀道，一直向天俯之国而
去，路上多有险阻，如果你要去的话，务必多加小心。入了城门，进
入荆州，你就等于到了中原了。
LONG );
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/clone/npc/xunbu" : 1,
                "/d/beijing/npc/ducha" : 1,
        ]));

        set("exits", ([  
               "east" : __DIR__"xidajie2",
        ]));
        set("outdoors", "jingzhou");

        set("coor/x", -7130);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}