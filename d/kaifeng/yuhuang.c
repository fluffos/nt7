inherit ROOM;

void create()
{
        set("short", "玉皇阁");
        set("long", @LONG
玉皇阁高十三米坐北朝南，采用仿木结构均用砖砌成。外观下阁
上亭。下圆下方，造型奇特，是一座集蒙古包与阁楼巧妙结合，具有
元代风格的建筑。阁内供有真武铜像一尊。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"sanqing",
                  "up" : __DIR__"yuhuang2",
        ]));

	set("coor/x", -5100);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}