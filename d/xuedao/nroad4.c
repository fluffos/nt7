inherit ROOM;

void create()
{
        set("short", "雪山山路");
        set("long", @LONG
大雪山北麓的地势不是甚高，周围还有一些小山丘。西面有一座
寺院依山而建。显得异常高大。寺院呈平顶梯型，多由大石砌成，墙
体厚实，窗口窄小。
LONG );
        set("exits", ([
                "north"   : __DIR__"nroad3",
                "westup"  : "/d/xueshan/shanmen",
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}
