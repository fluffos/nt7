
inherit ROOM;

void create()
{
        set("short", "内屋");
        set("long", @LONG
这里是回春堂专门出售药王庄弟子精心炮制的成药的地方。
药王谷有许多技艺高超的弟子，他们有时会炮制一些成药
就放在这里出售，疗效比一般的药材效果更佳。
LONG );

        set("no_clean_up", 1);
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"nanting",
        ]));
        set("objects", ([
                __DIR__"npc/huoji2" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
