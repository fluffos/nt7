// Room: /d/nanyang/yidao3.c
// Last Modified by Lonely on Nov. 20 2001

inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
你走在一条尘土飞扬的大官道上。四周人来人往。挑担子的行商，
赶着大车的马夫，上京赶考的书生，熙熙攘攘，非常热闹。不时还有两
三骑快马从身边飞驰而过，扬起一路尘埃。道路两旁是整整齐齐的杨树
林。
LONG );
        set("exits", ([
                "south" : __DIR__"beimen",
                "west" : "/d/kaifeng/tonanyang",
                "northeast" : "/d/ruzhou/xiaozheng",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "nanyang");
	set("coor/x", -6940);
	set("coor/y", 800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}