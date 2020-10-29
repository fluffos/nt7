inherit ROOM;

int is_chat_room()
{
	return 1;
}

void create()
{
        set("short", "客店茶房");
        set("long", @LONG
这里是扬州客栈的茶园，有许多无所事事的人都爱呆在这里，店
小二穿梭在客人中间，忙个不停。许多商人小贩也喜欢在这里向大家
兜售货物。
LONG );
        set("no_fight", 1);
        set("can_trade", 1);
        set("no_sleep_room", 1);

        set("exits", ([
                "south" : __DIR__"kedian",
        ]));

	set("coor/x", 10);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}