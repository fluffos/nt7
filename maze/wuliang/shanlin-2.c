// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "山坡");
	set("long", @LONG
这里是一个荒凉幽僻的山谷了，你沿着山坡的斜面向东面攀去，那面是一
片黑压压的森林了，你眼见段延庆一下子就逃进了黑林中。
LONG
	);
        set("outdoors", "大理");
	set("exits", ([
            "eastup" : __DIR__"shanlin-3",
	    "west" : __DIR__"shanlin-1",
	]));

	setup();
}