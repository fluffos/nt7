inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
你走着走着，突然发现你迷失了方向，你往回走的时候却发现那
已不是你来的道路了，你不禁心中一阵发麻。突然你在昏黄的灯光下，
隐约发现两边的汉白玉墙壁上刻着一些奇形怪状的符号(fuhao)。
LONG );
        set("exits", ([
                "south" : __FILE__,
                "north" : __FILE__,
                "east" : __DIR__"midao5",
                "west" : __FILE__,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}