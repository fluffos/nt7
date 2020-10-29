// shijie2.c

inherit ROOM;

void create()
{
        set("short", "石阶");
        set("long", @LONG
越往上，山势越陡峭，中间的石阶越窄，仅能一人行走，从这里
往上望，隐约望见一座石门。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "eastdown" : __DIR__"shijie1",
            "westup"   : __DIR__"shimen",
        ]));
        set("objects", ([
            CLASS_D("riyue") + "/zhaohe": 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}