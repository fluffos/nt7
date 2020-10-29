inherit __DIR__"binghuodao";

void create()
{
        set("short", "冰峰谷");
        set("long",
"这里是一处险要的峡谷，整个峡谷被冰雪覆盖，漫天雪花，尽\n"
"是白茫茫一片。不时传来几声狼嚎，令人毛骨悚然。\n"
);
        set("exits", ([ 
                "east"   : __DIR__"bingfenggu2", 
                "north"   : __DIR__"bingfengzhandao",
                "south"   : __DIR__"xiagu2",
        ]));

        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/binglang");
        
        setup();
}
