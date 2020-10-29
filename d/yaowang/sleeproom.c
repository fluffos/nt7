inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
这是一间宽大的房间，房间两旁放着两排竹床，四处打扫得
一尘不染，这里就是弟子们休息的地方。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
        "south" : __DIR__"ssl2",
]));

        set("sleep_room", 1);

        setup();
        replace_program(ROOM);
}
