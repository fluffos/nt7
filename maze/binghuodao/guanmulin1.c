inherit __DIR__"binghuodao";

void create()
{
        set("short", "灌木林");
        set("long",
"据说，凡是在蓬莱仙岛的凡人在意外死亡后魂魄都不会离开身\n"
"这里是冰火岛西岸海滩，海浪拍打着海边巨石。周围是一望无际的\n"
"大海，东边传来阵阵巨大的声响，地动山摇一般，似乎岛上的火山\n"
"在不断地喷发，释放出巨大的能量。\n"
);
        set("exits", ([ 
                "west"   : __DIR__"shenbingtan", 
                "southeast"   : __DIR__"shenmishandong",
        ]));

        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/shixueyeren");
                
        setup();
}
