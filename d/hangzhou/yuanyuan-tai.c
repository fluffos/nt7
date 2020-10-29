// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "圆缘台");
        set("long", @LONG
山道蜿蜒而上，面前出现了一块不大的平地，北边便是著名的月
老祠。留心祠前石碑，忽才知道身处的这片空地原来叫做『圆缘台』，
所谓千里姻缘一线牵，圆缘台正是意指圆满这姻缘的地方。环顾四周，
只见雾迷林麓，月照崖峰，风卷松浪，景色怡人，别饶佳趣。
LONG );
        set("outdoors", "xihu");
        set("exits", ([
                "north" : "/d/hangzhou/yuelao-ci",
                "east" : "/d/hangzhou/qixi-tai",
                "south" : "/d/hangzhou/shandao2",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/shusheng.c": 1,
        ]));
//        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -1970);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}