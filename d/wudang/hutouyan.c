inherit ROOM;

void create()
{
        set("short", "虎头岩");
        set("long", @LONG
一块巨大的岩石看上去好象一个虎头正张大了血盆大口咆哮，虎
身隐藏在草木丛中。
LONG );
        set("objects", ([
                "/clone/quarry/laohu" : 1,
        ]));
        set("exits", ([
                "northdown" : __DIR__"wulaofeng",
                "southup"   : __DIR__"chaotiangong",
        ]));

        set("outdoors", "wudang");
        set("coor/x", -350);
        set("coor/y", -360);
        set("coor/z", 140);
        setup();
        replace_program(ROOM);
}