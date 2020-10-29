inherit ROOM;

void create()
{
        set("short", "村间小路");
        set("long", @LONG
这是一条向东的青石大道，两边是一排排的乡间小屋。
LONG);

        set("exits", ([
                "west" : __DIR__"road1",
                "east" : __DIR__"shijiezhishu",
        ]));

        set("xinshoucun", 1); 
        set("outdoors", "newbie");
        set("no_pk", 1);
	setup();

        replace_program(ROOM);
}