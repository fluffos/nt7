inherit ROOM;

void create()
{
        set("short", "南盈门");
        set("long", @LONG
南盈门是开封城的南门，由于开封府尹治理有方，开封境内很是
平安。出城不远就是禹王台。
LONG );
        set("objects", ([
                  __DIR__"npc/guanbing" : 2,
                "/clone/npc/walker" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"jiedao2",
                  "south" : __DIR__"dadao",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5040);
	set("coor/y", 2130);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}