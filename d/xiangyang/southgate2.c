// Room: /d/xiangyang/southgate2.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "朱雀外门");
        set("long", @LONG
这里是襄阳城的南城门，只见城门上方刻着『朱雀门』三个大字。
城门高三丈，宽约二丈有余，尺许厚的城门上镶满了拳头般大小的柳
钉。门洞长约四丈，大约每隔两个时辰就换官兵把守。近年来蒙古屡
次侵犯襄阳城，故这儿把守相当严密，城内一些官兵们正在盘查要离
襄阳城的人。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "east"   : __DIR__"caodi4",
                "west"   : __DIR__"caodi5",
                "south"  : __DIR__"caodi6",
                "north"  : __DIR__"southgate1",
        ]));
        set("objects", ([
                __DIR__"npc/pi"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7820);
	set("coor/y", -820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}