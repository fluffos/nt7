inherit ROOM;

void create()
{
        set("short", "漕帮");
        set("long", @LONG
这里是漕帮的总部，说是什么漕帮，其实就是几个恶霸勾
结在一起在菜场这一块地方收收保护费，帮人打打架。几个流
氓正往里屋去。
LONG);

        set("exits", ([
                "north" : __DIR__"canchang",
                "enter" : __DIR__"liwu",                 
        ]));

        set("outdoors", "zhongzhou");
        set("coor/x", -9009);
	set("coor/y", -989);
	set("coor/z", 1);
	setup();
        replace_program(ROOM);
}