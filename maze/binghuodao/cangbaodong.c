inherit __DIR__"binghuodao";

void create()
{
        set("short", "藏宝洞");
        set("long",
"这里是一处幽深的洞穴，四处是断裂白骨，似乎曾经有人来过。\n"
"不知从何处传来阵阵低沉的吼声，令人毛骨悚然。\n"
);
        set("exits", ([ 
                "west"   : __DIR__"shenmishandong",
        ]));
        
        set("outdoors", 0);
        
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 2);
        set("s_npc", __DIR__"npc/bianyijiutoulong");
                
        setup();
}
