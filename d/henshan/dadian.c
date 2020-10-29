inherit ROOM;

void create()
{
        set("short", "大殿");
        set("long", @LONG
这里是南岳大殿，供祭祀炎帝之用。大殿结构为重檐歇山顶，顶
覆七彩琉璃。殿高七十二尺，正面七间，有石柱七十二根，合南岳七
十二峰之数。殿中南岳圣帝宝相庄严。南岳庙之雄为衡山小四绝之一。
 
LONG );
        set("exits", ([
                "south"  : __DIR__"yushulou",
                "north"  : __DIR__"houdian",
        ]));

        set("objects", ([
                __DIR__"npc/xiangke"  : 1,
                __DIR__"npc/youke"    : 1,
        ]));    

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}