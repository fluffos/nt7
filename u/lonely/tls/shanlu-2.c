inherit ROOM;

void create()
{
	set("short", "石板路");
	set("long", @LONG
    你走在一条长长的石板路上，道旁古树参天，鸟鸣不绝，这条
路上冷冷清请，你走了好长时间，也看不见一个人。
LONG	);
	set("exits", ([ /* sizeof() == 2 */
   "west" : __DIR__"shanlu-3",
  "east" : __DIR__"shanlu-1",

   
]));
	set("no_clean_up", 0);
	set("outdoors", "tianlongsi");

	set("coor/x",-430);
  set("coor/y",-320);
   set("coor/z",30);
   setup();
}
