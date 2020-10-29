//Room: minju5.c

inherit ROOM;

void create ()
{
        set ("short", "民居");
        set("long", @LONG
房间里甚是宽敞，里面摆设朴素而自然，左侧是一个古色古色的
精雅梳妆台，前面摆有两张红木圆椅。右侧墙壁上挂有一幅美女抚琴
图，上面配有几行笔迹清秀的隶体小字，内侧则是一张红色帐幔垂挂
的低矮木榻。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/huarui5",
        ]));

        set("coor/x", -10700);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}