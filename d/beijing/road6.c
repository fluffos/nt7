inherit ROOM;

void create()
{
        set("short", "大驿道");
        set("long", @LONG
你走在一条尘土飞扬的大驿道上。四周人来人往。挑担子的、行
商的、赶着大车的马夫、上京赶考的书生，熙熙攘攘，非常热闹。不
时还有两三骑快马从身边飞驰而过，扬起一路尘埃。道路两旁是整整
齐齐的杨树林。从这里远远的就可以望见北京城。西南是通往恒山。
LONG );
        set("exits", ([
                "northwest" : "/d/beijing/road5",
                "southwest" : "/d/hengshan/jinlongxia",
                "southeast" : "/d/beijing/road7",
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7590);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}