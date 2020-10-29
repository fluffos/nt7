//Room: minju1.c

inherit ROOM;

void create ()
{
        set ("short", "民居");
        set("long", @LONG
这里是一家民居住房，窗台上放着大大小的小陶盆瓷罐，里面种
着花草之类的东西，两扇窗子大开，飘出一股花草的清香味。民居里
十分热闹，一张大木桌子，周围放着几把椅子，几个邻里凑在一起，
不知在谈什么。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/huarui1",
        ]));

        set("coor/x", -10750);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}