inherit ROOM;

void create()
{
        set("short", "西角楼");
        set("long", @LONG
角楼是建于城墙之上，用于兵卫守望的处所，只在楼的顶端挂上
一盏灯笼，从此远眺，远处山水亭台，一一在目，西面下去就是西大
街。来往的行人不断。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "eastdown" : __DIR__"zhuque",
                  "westdown" : __DIR__"wroad2",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2240);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}