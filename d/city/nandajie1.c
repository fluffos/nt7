// Room: /city/nandajie1.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "南大街");
        set("long", @LONG
南大街乃是城里的繁华地段，一到晚上，一派灯红酒绿，尤为热
闹。笑声、歌声、琴声、箫声，汇成一片送入了你的耳朵，你不禁心
猿意马，很想就此停步享受一番。北边是一个热闹的广场。东边是一
家店铺，墙上画着个斗大的『当』字，仔细倾听，可以听到压低的讨
价还价的声音。西边则是一片喧嚣，欢呼声、大骂声不绝于耳，夹杂
着『一五一十』的数钱声，原来那是方圆千里之内最大的一家赌场。
LONG );
        set("outdoors", "city");
	set("exits", ([
		"east"  : "/d/city/dangpu",
		"south" : "/d/city/nandajie2",
		"west"  : "/d/city/duchang",
		"north" : "/d/city/guangchang",
	]));
	set("objects", ([
		"/d/city/npc/hunhun" : 1,
		"/d/city/npc/liumang": 4,
		"/d/city/npc/liumangtou" : 1,
		"/clone/npc/xunbu" : 1,
	]));

	set("coor/x", 0);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
