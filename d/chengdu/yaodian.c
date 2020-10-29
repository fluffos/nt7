// Room: yaodian.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "济世堂药店");
        set("long", @LONG
济世堂药店卖很多中原买不到的药。托唐门的福，生意一直都很
好。一走进这家药店，就闻到一股股浓烈刺鼻的药味。你正奇怪药店
伙计怎麽能忍受，就看到药店里还有一些人正拿奇怪的眼光看你。他
们的腰间鼓鼓囊囊的，显然不是好惹的。
LONG );
        set("objects", ([
                __DIR__"npc/huoji" : 1,
        ]));
        set("exits", ([
                "southeast" : __DIR__"westroad3",
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15250);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}