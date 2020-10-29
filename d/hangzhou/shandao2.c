// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "山道");
        set("long", @LONG
蜿蜒而上的山道渐渐陡峭，高大的林木后面隐隐约约露出天空中
飘荡的飞絮。野花满径，花香浓浓缭绕在呼吸里。耳畔时而想起潺潺
的流水声，环顾翠绿的山谷，却又找不见溪流的踪影。
LONG );
        set("outdoors", "xihu");
        set("exits", ([
                "north" : "/d/hangzhou/yuanyuan-tai",
                "south" : "/d/hangzhou/shandao1",
        ]));

//        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -1980);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}