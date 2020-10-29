inherit __DIR__"binghuodao";

void create()
{
        set("short", "火焰谷");
        set("long",
"火焰谷内地动山摇，似乎从未平静过。不远处无数大小火山正\n"
"争先恐后的喷发着，谁也不肯停下的样子。这里热气腾腾，令人异\n"
"常难受，如果说还有生物的话，那肯定是经过千万年进化的精怪。\n"
);
        set("exits", ([ 
                "east"   : __DIR__"huoyangu2", 
                "north"   : __DIR__"xiagu2",
                "south"   : __DIR__"huoyanshiqiao",
        ]));
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/huohu");               
        setup();
}
