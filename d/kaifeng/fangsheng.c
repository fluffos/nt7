inherit ROOM;

void create()
{
        set("short", "放生池");
        set("long", @LONG
从三尺台阶走下就是大街了。台阶旁挖了一个小池子，边上用白
石围起了栏杆。北边的池壁上『放生池』几个字涂成了红色。由于池
的一边靠近街道，方便别人作出善举，但整天见人把鱼放下，却是去
总看不见踪影，多半是被附近的泼皮无赖晚上摸来作宵夜了。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"qianshou",
                  "westdown" : __DIR__"wroad",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "xiangguosi");

	set("coor/x", -5060);
	set("coor/y", 2220);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
