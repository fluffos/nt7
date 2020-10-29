//Room: yongtai-beikou.c

inherit ROOM;

void create ()
{
        set ("short", "永泰北口");
        set("long", @LONG
麒祥街的西尽头，一根三丈多高的旗杆之上，挑起了四盏斗大的
灯笼，每当暮色降临，这里灯火通明。北面是一家珠宝行，里面隐隐
散出诱人的珠光宝气，很多妇人路过这里都不免要往里瞧一瞧。南方
通向永泰大道。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "east" : "/d/changan/qixiang1",
                "north" : "/d/changan/zhubaohang",
                "south" : "/d/changan/yongtai-dadao1"
        ]));

        set("outdoors", "changan");  
        set("coor/x", -10760);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}