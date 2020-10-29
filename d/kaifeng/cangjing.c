inherit ROOM;

void create()
{
        set("short", "藏经楼");
        set("long", @LONG
藏经楼是一栋两层小楼，阁楼中都是佛家经典，名贵稀少的都用
檀木盒盛放了。收藏在楼上，派有专人职司。你满眼看去，到处是高
低的书架，
LONG );
        set("objects", ([
                  __DIR__"npc/zhifa" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"houyuan",
                  "up" : __DIR__"cangjing2",
                  "east" : __DIR__"xiaoyuan",
        ]));

	set("coor/x", -5030);
	set("coor/y", 2220);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}