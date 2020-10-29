inherit ROOM;

void create()
{
        set("short", "青石小路");
        set("long", @LONG
这是一条向东的青石大道，两边是一排排的乡间小屋。
LONG);

        set("exits", ([
                "east" : __DIR__"lianwuchang",
                "west" : __DIR__"shijiezhishu",
                "north": __DIR__"cunzhangjia",
                "south": __DIR__"zahuopu",
        ]));

        set("xinshoucun", 1); 
        set("outdoors", "newbie");
	set("no_pk", 1);
	setup();

        replace_program(ROOM);
}
