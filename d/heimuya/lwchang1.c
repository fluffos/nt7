// lwchang1.c
// By haiyan

inherit ROOM;

void create()
{
        set("short", "练武场");
        set("long", @LONG
这里是日月神教的练武场，场上立着几个木人，教中众弟子常在
此处修炼邪功，四周充满着诡秘色彩。
LONG );
        set("exits", ([
            "west"      : __DIR__"midao02",
        ]));
        set("objects", ([
            "/clone/npc/mu-ren" : 4,
        ]));

        setup();
        replace_program(ROOM);
}
