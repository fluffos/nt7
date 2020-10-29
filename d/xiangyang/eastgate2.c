// Room: /d/xiangyang/eastgate2.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "青龙外门");
        set("long", @LONG
这里是襄阳城的东城门，只见城门上方刻着『青龙门』三个大字。
城门高三丈，宽约二丈有余，尺许厚的城门上镶满了拳头般大小的柳
钉。门洞长约四丈，大约每隔两个时辰就换官兵把守。近年来蒙古屡
次侵犯襄阳城，故这儿把守相当严密，城内一些官兵们正在盘查要离
襄阳城的人。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "west"  : __DIR__"eastgate1",
                "east"  : "/d/city2/yidao",
                "northeast"  : "/d/jianzhong/shanlu1",
        ]));
        set("objects", ([
                __DIR__"npc/pi"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7770);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me,string dir)
{
       if( dir == "east" && !wizardp(me) 
            && !query_temp("warquest", me) )
       return notify_fail("军营重地，闲杂人等，不得入内！\n");

       return ::valid_leave(me,dir);
}