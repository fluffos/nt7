// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "问心泉");
        set("long", @LONG
问心泉躺卧在山麓的沟谷里，溅珠喷雪，下垂若帘。有诗云：』
行到山深处，帘泉一画图。岩空悬百尺，涧响落千珠。春雨流通急，
秋云滴不枯。』然而问心泉闻名的并不是它的美景，而是『问心』这
一泉名。心错而情错，情孽油生。上山拜月老的人，不妨在这里饮一
掬清泉，扪心自问。是有情人终成眷属，若错姻缘早离早散。
LONG );

        set("outdoors", "xihu");
        set("exits", ([
                "east" : "/d/hangzhou/shandao1",
         ]));

        set("objects", ([
                "/d/hangzhou/npc/qinger": 1,
        ]));

	set("coor/x", 760);
	set("coor/y", -1990);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}