inherit ROOM;

void create()
{
	set("short", "石板路");
	set("long", @LONG
    你走在一条长长的石板路上，道旁古树参天，鸟鸣不绝，这条
路上冷冷清请，你走了好长时间，也看不见一个人。东面就是龙象台
了。
LONG	);
	set("exits", ([ /* sizeof() == 2 */
   "west" : __DIR__"shanlu-2",
  "east" : __DIR__"longxiang4",
   
]));
	set("no_clean_up", 0);
	set("outdoors", "tianlongsi");

	set("coor/x",-420);
  set("coor/y",-320);
   set("coor/z",30);
   setup();
}
