inherit ROOM;

void create ()
{
        set ("short","西门");
        set ("long", @LONG
这里是武汉的西门了。有很多商旅和武林人士进进出出。有几个官
兵在这里检查来往的行人。旁边站着一名军官，看起来神气十足，不停
地指手画脚。
LONG);

        set("exits", ([
                "east":__DIR__"hzjie4",
                "west":"/d/jingzhou/guandao1",
        ]));
        set("objects",([
                "/d/city/npc/bing":2,
                "/d/city/npc/wujiang" :1,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5110);
	set("coor/y", -1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}