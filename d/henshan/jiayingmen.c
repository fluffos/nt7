inherit ROOM;

void create()
{
        set("short", "嘉应门");
        set("long", @LONG
这里是地方官迎接京师御史官来祭南岳的地方，是南岳大庙第五
进门了。门上雕塑也较精细些，悬彩灯笼时时换新。
LONG );
        set("exits", ([ 
               "south"  : __DIR__"yubeiting",
               "north"  : __DIR__"yushulou",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}