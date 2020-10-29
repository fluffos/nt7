//  Room:  /d/luoyang/road0.c

inherit  ROOM;

void  create  ()
{
        set("short",  "大官道");
        set("long",  @LONG
这是一条宽阔笔直的官道，足可容得下十马并驰。往东通向脂粉之
都的扬州，而西面则是号称“扼九州”的虎牢关了。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east" : __DIR__"road11",
                "northwest" : __DIR__"road2",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6900);
	set("coor/y", 2140);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}