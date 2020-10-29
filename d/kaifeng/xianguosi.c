inherit ROOM;

void create()
{
        set("short", "相国寺");
        set("long", @LONG
大相国寺占地五百余亩，辖六十四个禅，律院，养僧千余。是京
城最大的寺院和全国佛教活动中心。门前『大相国寺』的匾额乃是当
今御笔亲书。大门敞开，多有行人来往。
LONG );
        set("objects", ([
                  __DIR__"npc/zhike" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"qianyuan",
                  "south" : __DIR__"jiedao",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5040);
	set("coor/y", 2170);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}