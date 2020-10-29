// shijie1.c

inherit ROOM;

void create()
{
        set("short", "石阶");
        set("long", @LONG
山路突然陡峭，两旁山峰笔立，中间留出一条窄窄的石阶，仅能
两人并肩而行。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "eastdown" : __DIR__"shandao2",
            "westup"   : __DIR__"shijie2",
        ]));
        set("objects", ([
            CLASS_D("riyue") + "/fansong": 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}