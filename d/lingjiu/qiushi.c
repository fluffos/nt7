inherit ROOM;

void create()
{
        set("short", "囚室");
        set("long", @LONG
这里是「灵鹫宫」关押犯人的地方，屋中光线昏暗，气味难闻。
现在这里静悄悄的，似乎虚竹子当上门主后，这里便比以前轻静了许
多。
LONG );
        set("exits", ([
                "east" : __DIR__"men1",
        ]));
        set("objects",([
                "/d/lingjiu/npc/wulaoda" : 1,
        ]));

        setup();
        replace_program(ROOM);
}