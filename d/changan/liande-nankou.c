//Room: liande-nankou.c

inherit ROOM;

void create ()
{
        set ("short", "连德南口");
        set("long", @LONG
华瑞街的东尽头，一根三丈多高的旗杆之上，挑起了四盏斗大的
灯笼，每当暮色降临，这里灯火通明。南面有一家小酒馆，里面隐隐
传来划拳行令的声音。北方通向连德大道。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "west" : "/d/changan/huarui6",
                "north" : "/d/changan/liande-dadao5",
                "south" : "/d/changan/xiaojiuguan"
        ]));

        set("outdoors", "changan");  
        set("coor/x", -10680);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}