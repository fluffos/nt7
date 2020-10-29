inherit ROOM;

void create()
{
        set("short", "州桥");
        set("long", @LONG
这座高高的桥如同彩虹初降人间，三十六道石阶直通桥面桥下就
是水流奔涌的大运河。桥上人来如梭河中巨舟横过。切然在桥下看去，
人行于高波之上，令人心颤不已。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "southdown" : __DIR__"road3",
                  "northdown" : __DIR__"road5",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2230);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}