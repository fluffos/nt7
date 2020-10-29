inherit ROOM;
void create()
{
        set("short", "地道");
        set("long",
"前面终于出现一道光明，漫长的地道走到了尽头。回头看看来路一片\n"
"模糊。\n"
);
        set("exits", ([
        "up" : "/d/llszhuang/dynamic/jiuqu14",
]));
        set("no_magic", "1");
        setup();
}
