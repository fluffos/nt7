// Room: /d/northft/ftn13.c

inherit ROOM;

void create()
{
	set("short", "小径");
	set("long", @LONG
这是一条窄窄的上山小路，两旁怪石嶙峋，中间的路倒是很
平坦，看样子是被人专门开掘出来的。向东望去是一大片乱石岗。
LONG
	);
	set("exits", ([
	"west" : __DIR__"ftn12",
	"east" : __DIR__"iron_mine/entry",
]));

	setup();
	replace_program(ROOM);
}
