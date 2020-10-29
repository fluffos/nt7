// road4.c
// by Xiang

inherit ROOM;

void create()
{
        set("short", "黄土路");
        set("long", @LONG
你走在一条黄土路上。这里是山西地界，往东就进入河北了。现
在这里不是太平时节，还是快点走吧。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
                "northeast" : __DIR__"road1",
                "southwest" : __DIR__"dukou1",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}