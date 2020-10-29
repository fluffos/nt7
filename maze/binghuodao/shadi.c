inherit __DIR__"binghuodao";

void create()
{
        set("short", "沙地");
        set("long",
"这里是一片沙地，是由海滩的巨浪冲刷而成。然后走在沙地上，\n"
"却感觉从脚心传来阵阵热气，似乎着沙地下面蕴藏着什么东西。\n"
);
        set("exits", ([ 
                "west"    : __DIR__"haitan", 
                "north"   : __DIR__"haitan1", 
                "south"   : __DIR__"haitan2", 
                "east"    : __DIR__"guanmucong", 
        ]));


        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/chihuoshe");

        setup();
}
