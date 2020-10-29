// This program is a part of NT MudLIB

inherit RIVER;

void create()
{
        set("short", "汉水北岸");
        set("long", @LONG
汉水北岸也是相当热闹，自北岸渡口往北，一条笔直的官道直通南
阳。此地民风淳朴，路旁夹柳成阴，酒厮林立，且都有一面大大的「酒
」旗迎风飘扬，蔚为壮观。也有不少小贩沿路叫买，语多难辨，却也令
人盛情难却。
LONG );

        set("outdoors", "nanyang");
        set("region", "nanyang_zone");
        set("to", __DIR__"hanshui1");

        set("exits", ([
                "north" : __DIR__"nanmen",
        ]));

        set("objects", ([
                __DIR__"npc/chuanfu2" : 1,
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));
        set("no_clean_up", 0);
	set("coor/x", -6940);
	set("coor/y", 740);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}
