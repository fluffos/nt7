// Room: chufang.c

inherit ROOM;
void create()
{
        set("short", "酒楼厨房");
        set("long", @LONG
这里是酒楼后面的厨房，几个大水池前面有不少的伙计在摘菜和
清洗碗碟，还有一些伙计站在油烟直冒的油锅面前努力的翻炒着各色
菜肴，而一个粗手大脚的中年厨娘大声吆喝，指手画脚的却不干活。
LONG );
        set("exits", ([
                "west" : __DIR__"jiudian",
        ]));
        set("objects", ([
                __DIR__"npc/chuniang" : 1,
        ]) );
        set("no_fight", 1);
        set("no_sleep_room", 1);
        set("coor/x", -15180);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}