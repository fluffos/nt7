inherit __DIR__"binghuodao";

void create()
{
        set("short", "神秘山洞");
        set("long",
"这是一处神秘的洞穴，跟普通峡谷内的洞穴一样，这里显得十\n"
"分宽敞，却又异常潮湿。洞壁四周粘连着绿色的液体，阵阵低吼从\n"
"洞深处传来，令人不寒而栗。\n"
);
        set("exits", ([ 
                "northwest"   : __DIR__"guanmulin1", 
                "southwest"   : __DIR__"guanmulin2",
                "east"   : __DIR__"cangbaodong",
        ]));
        
        set("outdoors", 0);
        
        set("n_time", 60);
        set("n_npc",1);
        set("n_max_npc", 2);
        set("s_npc", __DIR__"npc/jiutoulong");  
        setup();
}
