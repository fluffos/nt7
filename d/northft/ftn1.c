// Room: /d/northft/ftn1.c

inherit ROOM;

void create()
{
	set("short", "青石小路");
	set("long", @LONG
这是奉天城北门外一条青石铺成的小路，南面就是奉天城的
北门了。路边稀疏的长着一些荒草，路上满是沙砾，阵阵北风呼
啸而过，越发给人一种凄凉的感觉。
LONG
	);
	set("exits", ([
  "south" : "/d/fengtian/out_fengtian_n",
  "north" : __DIR__"ftn2",
]));

	set("outdoors", "northft");

	setup();
}
