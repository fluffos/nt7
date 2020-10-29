//  Room: /d/luoyang/road11.c

inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
这是一条宽阔笔直的官道，足可容得下十马并驰。道路两边，是一
排排高树。树林之外，便是一片片的农田了。大道往东通向脂粉之都的
扬州，而西面则是通往洛阳城。
LONG);
        set("exits", ([  /*  sizeof()  ==  2  */
                "east" : __DIR__"road10",
                "west" : __DIR__"road0",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6890);
	set("coor/y", 2140);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}