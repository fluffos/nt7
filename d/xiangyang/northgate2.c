// Room: /d/xiangyang/northgate2.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "玄武外门");
        set("long", @LONG
这里是襄阳城的北城门，只见城门上方刻着『玄武门』三个大字。
城门高三丈，宽约二丈有余，尺许厚的城门上镶满了拳头般大小的柳
钉。门洞长约四丈，大约每隔两个时辰就换官兵把守。近年来蒙古屡
次侵犯襄阳城，故这儿把守相当严密，城内一些官兵们正在盘查要离
襄阳城的人。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "south"  : __DIR__"northgate1",
                "north"  : __DIR__"caodi3",
                "east"   : __DIR__"caodi1",
                "west"   : __DIR__"caodi2",
        ]));
        set("objects", ([
                __DIR__"npc/pi"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7810);
	set("coor/y", -710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}