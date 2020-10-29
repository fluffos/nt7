inherit ROOM;

void create()
{
        set("short", "荆棘丛");
        set("long", @LONG
这里是一片茂密的荆棘丛，中间隐隐约约有一条小道，丛中
开着一些不知名的小花，空气中弥漫着一种刺鼻的味道。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"shangpo1",
  "south" : __DIR__"jingji1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
