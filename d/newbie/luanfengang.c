inherit ROOM;

void create()
{
        set("short", "乱坟岗");
        set("long", @LONG
这里一片都是坟墓，不知道埋了多少英雄好汉，多少巨奸
大恶，让人不禁生出了人生不过如此的悲凉之意。不过如烟火
一样，即便是短暂也能发出眩目的光彩，一念及此，你不由收
起悲观的念头，热血澎湃，恨不得立即投身江湖快意恩仇，去
争取名垂青史。
LONG);
        set("exits", ([
                "northwest" : __DIR__"luanshigang",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("no_pk", 1);
	setup();

        replace_program(ROOM);
}