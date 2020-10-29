inherit __DIR__"binghuodao";

void create()
{
        set("short", "冰雪峡～谷");
        set("long",
"路的尽头依然是一处巨大的峡谷，四周被高耸的山峰包围，山\n"
"峰又被厚厚的积雪覆盖，不时传来几声巨大的吼叫，峡谷之后似乎\n"
"藏着巨大的神兽。\n"
);
        set("exits", ([ 
                "south"   : __DIR__"bingfengzhandao", 
        ]));
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 2);
        set("s_npc", __DIR__"npc/binglong");
        
        setup();
}
