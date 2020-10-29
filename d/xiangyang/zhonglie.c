// Room: /d/xiangyang/zhonglie.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "忠烈祠");
        set("long", @LONG
这里是襄阳城的忠烈祠，十余年来为保卫襄阳而牺牲的烈士遗骨
都安葬在这里，每个有爱国心的好汉到这都会来祭奠一下忠魂。
LONG );
        set("no_beg", 1);
        set("no_clean_up", 0);

        set("exits", ([
                "west" : __DIR__"eastroad2",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("coor/x", -7790);
	set("coor/y", -750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}