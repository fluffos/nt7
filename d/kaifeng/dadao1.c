inherit ROOM;

void create()
{
          set ("short", "三叉路口");
        set("long", @LONG
道路至此分为三路，一条路向北就是开封城，东南面是座树林。
林中隐有条小道穿过。西南面的路通向野猪林。
LONG );

          set("outdoors", "kaifeng");
          set("exits", ([
                  "southwest" : __DIR__"dadao2",
                  "southeast" : __DIR__"shulin",
                  "north" : __DIR__"dadao",
        ]));

	set("coor/x", -5040);
	set("coor/y", 2110);
	set("coor/z", 10);
	setup();
          replace_program(ROOM);
}