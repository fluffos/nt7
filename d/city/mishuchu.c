// mishuchu.c
// By haiyan

inherit ROOM;

void create()
{
        set("short", "报名处");
        set("long", @LONG
这里是武林大会的报名处。如果你想参加一年一度的武林盛会一
显身手，夺取武林五绝之名，可以在大会开始时在这里报名。参加有
奖竞猜的江湖人士也可以在这里购买彩票参加竞猜活动。
LONG );
        set("exits", ([
                "north" : "/d/city/wudao1",
        ]));
        set("objects", ([
                "/clone/npc/missyu" : 1,
        ]));
        set("no_fight", 1);
        setup();
        replace_program(ROOM);
}
