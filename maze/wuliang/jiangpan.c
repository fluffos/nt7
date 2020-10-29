// jiangban.c
// bbb 1997/07/20
// Modify By River 98/12
inherit ROOM;

void create()
{
        set("short", "江畔");
	set("long", @LONG
外边怒涛汹涌，水流湍急，江岸山石壁立，嶙峋巍峨，看这情势，已是到
了澜仓江边，容身处离讲面有十来丈高，江水纵然大涨，也不会淹到此处江岸
全是山石。
LONG
	);

	set("exits", ([
           "enter" : __DIR__"taijie",
           "down" : __DIR__"anbian1",
	]));
        set("outdoors", "大理");
	setup();
}