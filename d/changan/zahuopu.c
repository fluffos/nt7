//Room: zahuopu.c

inherit ROOM;

void create()
{
        set("short", "杂货铺");
        set("long", @LONG
一间老字号的杂货铺。祖孙三代经营下来，在长安城南一带已经
有了一些小名气。这里无论是油盐酱醋，还是大米白面，老百姓日常
生活需要的东西一样都不少。再加上这里的老掌柜待客如宾，杂货铺
的生意看来一天比一天好。
LONG );
        set("exits", ([
                "south" : "/d/changan/huarui5",
        ]));
        set("objects", ([
                "/d/changan/npc/liu": 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10700);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}