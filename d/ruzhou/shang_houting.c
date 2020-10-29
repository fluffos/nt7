inherit ROOM;

void create()
{
        set("short", "后厅");
        set("long", @LONG
这里是商家堡的后厅所在，大厅相当的宽敞明亮，四周的墙
上悬挂满了各朝名人的真迹。
LONG);
        set("exits", ([
                "north"  : __DIR__"shang_zoulang1",
                "south"  : __DIR__"shang_dating",
                "west"  : __DIR__"shang_xiangw",
                "east"  : __DIR__"shang_xiange",
        ]));
	set("coor/x", -6750);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}