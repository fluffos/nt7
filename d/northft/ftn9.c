// Room: /d/northft/ftn9.c

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
这是一条窄窄的上山小路，两旁怪石嶙峋，中间的路倒是很
平坦，看样子是被人专门开掘出来的。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "westdown" : __DIR__"ftn8",
  "east" : __DIR__"ftn10",
]));

	set("outdoors", "northft");
	setup();
	replace_program(ROOM);
}
