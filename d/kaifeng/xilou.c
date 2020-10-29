inherit ROOM;

void create()
{
        set("short", "戏楼");
        set("long", @LONG
一座木头粗粗搭起的高台，台的后端用大的帘子遮了起来那后头
就是戏子装扮上台的地方。由于是关帝庙的缘故，演的无非是桃园三
结义，单骑走千里。杯酒斩文聩等故事。
LONG );
        set("objects", ([
                  __DIR__"npc/qingyi" : 1,
                  __DIR__"npc/xiaosheng" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"paifang",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5010);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}