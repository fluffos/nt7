//Room: /d/city/shuyuan2.c

#define STORY_TOC "/doc/legend/toc"
inherit ROOM;

void create()
{
        set("short", "书院书库");
        set("long", @LONG
这里是书院的图书馆，窗明几净，一尘不染。壁上的书架 (shel
f)堆满侠客行的先贤们的文选，记录了侠客行的风风雨雨和无数凄婉
的、遥远磨灭不去的传说。你可以阅读(read)到这些古老的故事。
LONG );
        set("item_desc", ([
            "shelf" : "此处已经被衙门查封了。\n",
        ]));
        set("objects", ([
                "/d/room/roomnpc/teagirl":1,
        ]));
        set("exits", ([
            "down" : "/d/city/shuyuan",
        ]));
	set("no_clean_up", 0);
	set("coor/x", 10);
	set("coor/y", 10);
	set("coor/z", 10);
	setup();
}