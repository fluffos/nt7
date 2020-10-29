inherit ROOM;

void create()
{
        set("short", "戏院后台");
        set("long", @LONG
这里是长安戏院的后台，后台不大，却打扫得很干净。几个戏子
正在后台化妆，看见你来了，都用很奇怪的眼神盯着你。
LONG );
        set("exits", ([
                "south" : "/d/beijing/xiyuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/q" : 10,
        ]));

        setup();
        replace_program(ROOM);
}

