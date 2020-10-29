inherit ROOM;
void create()
{
        set("short", "地道");
        set("long",
"黑漆漆的地道，你不知道要爬多久才能出去。\n"
);
        set("exits", ([
  "up" : __DIR__"didao1",
]));
        set("no_magic", "1");
        setup();
}
