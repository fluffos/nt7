inherit __DIR__"binghuodao";

void create()
{
        set("short", "灌木林");
        set("long",
"浓密的灌木丛，不合时宜的生长在此处，似乎是受到了一些特\n"
"殊的环境所影响，灌木丛中隐约有什么奇怪的响动。\n"
);
        set("exits", ([ 
                "west"   : __DIR__"shenghuotan", 
                "northeast"   : __DIR__"shenmishandong",
        ]));

        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/shixueyeren");
        
        setup();
}
