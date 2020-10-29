inherit __DIR__"binghuodao";

void create()
{
        set("short", "冰峰栈道");
        set("long",
"这里是靠近峡谷的一处栈道，只见栈道竟由一根根冰柱连贯而\n"
"成。冰雪漫天，前方一片茫茫，似乎看不到尽头。\n"
);
        set("exits", ([ 
                "south"   : __DIR__"bingfenggu", 
                "north"   : __DIR__"bingxuexiagu",
        ]));
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/binglangren");
        
        setup();
}
