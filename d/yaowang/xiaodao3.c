inherit ROOM;

void create()
{
        set("short", "丛林小道");
        set("long", @LONG
这是一条僻静的丛林小道，小道上满是枯枝败叶，踩上去非
常松软，四周静悄悄的，偶尔传来几声鸟鸣。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "southeast" : __DIR__"xiaodao2",
  "northwest" : __DIR__"xiaodao4",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
