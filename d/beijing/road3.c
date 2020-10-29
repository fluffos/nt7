inherit ROOM;

void create()
{
        set("short", "大驿道");
        set("long", @LONG
你走在一条尘土飞扬的大驿道上。四周人来人往。挑担子的、行
商的，赶着大车的马夫，上京赶考的书生，熙熙攘攘，非常热闹。不
时还有两三骑快马从身边飞驰而过，扬起一路尘埃。道路两旁是整整
齐齐的杨树林。东北方向是另一条大道。
LONG );
        set("exits", ([
                "northeast" : "/d/guanwai/laolongtou",
                "northwest" : "/d/beijing/road2",
                "south"     : "/d/beijing/road4",
        ]));
        set("objects",([
                "/d/taishan/npc/shu-sheng" : 1,
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2770);
	set("coor/y", 7590);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}