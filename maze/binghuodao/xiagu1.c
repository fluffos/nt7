inherit __DIR__"binghuodao";

void create()
{
        set("short", "峡谷");
        set("long",
"这里是一处平常的峡谷，峡谷蜿蜒前行，看看不到尽头。不过\n"
"令人惊奇的是，峡谷北端寸草不生，南端却草木茂盛，同一峡谷却\n"
"有着两种迥异的景象，真是匪夷所思。\n"
);
        set("exits", ([ 
                "west"   : __DIR__"guanmucong", 
                "east"   : __DIR__"xiagu2",
        ]));

        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/yeren");
        
        setup();
}
