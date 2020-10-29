inherit ROOM;

void create()
{
        set("short", "茅草屋");
        set("long", @LONG
这是一间简陋的茅草屋，正对面是一张土炕，炕上只有一床
席子和一个竹枕头。右面的一个大木架子上摆着近百种各样的药
材，满屋充斥着刺鼻的药味。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
        "east" : __DIR__"lu2",
]));

        setup();
        replace_program(ROOM);
}
