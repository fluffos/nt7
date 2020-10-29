#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "芙蓉峰");
        set("long", @LONG
芙蓉峰是衡山五峰之一，据说芙蓉峰下有个山洞，洞中长满了芙
蓉花，长年不谢，芙蓉峰也因此得名。但见此处环境清幽，草木葱绿，
这里不如祝融峰高，冷暖适宜，实在是个人间仙境。
LONG );

        set("exits", ([
                "southeast"   : __DIR__"shanlu13",
        ]));

        set("objects", ([
                CLASS_D("henshan") + "/liu" : 1,
                CLASS_D("riyue") + "/qu" : 1,
        ]));    

        set("no_clean_up", 0);

	set("coor/x", -6960);
	set("coor/y", -5520);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}