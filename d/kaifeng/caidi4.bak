inherit ROOM;

void create()
{
        set("short", "菜地");
        set("long", @LONG
这片菜园子几畦地里种了一些时鲜蔬菜。另外有几个木桩搭起的
菜架子，供一些爬藤的蔬菜生长，不过你举目看去，老大的一片菜园
子，居然疏疏落落的没有几棵菜。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"caidi",
                  "west" : __DIR__"caidi2",
        ]));
        set("outdoors", "xiangguosi");

	set("coor/x", -5000);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
