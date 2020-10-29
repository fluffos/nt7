// Room: /ruzhou/jiulou1.c
// YZC 1995/12/04 llm 99/07

inherit ROOM;

void create()
{
        set("short", "迎宾楼");
        set("long", @LONG
方圆数百里内，迎宾楼的名气可谓是不小。来此落脚的名士雅客
也为其题匾作诗，流下不少令其得意的东西。楼下布置简易，顾客多
是匆匆的行人，买点包子，鸡腿、米酒就赶路去了。楼上是专门举办
备类婚宴的喜福堂。
LONG
        );

        set("exits", ([
                "north" : __DIR__"xidajie",
                "up" : __DIR__"xifu-tang",
        ]));

        set("objects", ([
      __DIR__"npc/xiaoer" : 1,
        ]));

	set("coor/x", -6770);
	set("coor/y", 1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}