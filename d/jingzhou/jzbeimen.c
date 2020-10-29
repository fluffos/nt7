inherit ROOM;

void create()
{
        set("short", "荆州北门" );
        set("long", @LONG
这里是荆州的北门，由于荆州历来都是军事要地，因此城墙坚实
无比，城楼高高耸立，由于北门以外，人烟稀少，来往的人不多，所
以官兵的防卫也就不十分严密。
LONG );
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/clone/npc/xunbu" : 1,
                "/d/beijing/npc/ducha" : 1,
        ]));
        set("exits", ([
                "northup" :"/d/wudang/wdroad5",
                "south" :__DIR__"beidajie2",
  
        ]));
        set("outdoors", "jingzhou");
        set("coor/x", -7100);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}