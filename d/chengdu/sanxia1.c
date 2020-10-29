#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "西陵峡");
        set("long", @LONG
这里便是长江三峡的西陵峡，长江两岸高山耸立，遮天蔽日，真
可谓是猿猴愁末攀啊！由于这里河道比较窄，河水变的不安起来，发
出阵阵咆哮声，不时翻滚着旋涡向东流去。
LONG );
        set("exits", ([
                  "west" : __DIR__"sanxia2",
                "southeast" : __DIR__"shudao10",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15090);
	set("coor/y", -1820);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}