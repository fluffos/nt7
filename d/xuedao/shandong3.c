inherit ROOM;

void create()
{
        set("short", "山洞");
        set("long", @LONG
这是一个小小的山洞，血刀老祖的藏身之地。由於此地比较隐秘，
仇家很难寻到这来。洞底有一张供桌，上面供了什麽东西，你看不清。
壁上画了一些模糊不清的文字图案，也不知道是些什么。
LONG );
        set("exits", ([
                "out" : __DIR__"shandong2",
                "east": __DIR__"xiuxishi",
        ]));
        set("objects", ([
                CLASS_D("xuedao")+"/laozu" : 1,
                //CLASS_D("xuedao")+"/first" : 1,
                __DIR__"npc/x_lama" : 2,
        ]));
        set("valid_startroom", 1);
        setup();
        replace_program(ROOM);

        "/clone/board/xuedao_b"->foo();
}
