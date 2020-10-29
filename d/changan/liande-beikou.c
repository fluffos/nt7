//Room: liande-beikou.c

inherit ROOM;

void create ()
{
        set ("short", "连德北口");
        set("long", @LONG
麒祥街的东尽头，一根三丈多高的旗杆之上，挑起了四盏斗大的
灯笼，每当暮色降临，这里灯火通明。北面有一座竹棚，里面隐隐传
来唱戏的声音。南方通向连德大道。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "west" : "/d/changan/qixiang6",
                "north" : "/d/changan/xiyuan",
                "south" : "/d/changan/liande-dadao1"
        ]));

        set("outdoors", "changan");  
        set("coor/x", -10680);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}