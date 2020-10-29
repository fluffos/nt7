inherit __DIR__"binghuodao";

void create()
{
        set("short", "火焰石桥");
        set("long",
"这里是位于火焰谷到烈火峡谷之间的一处石桥。这里寸草不生。\n"
"抬头之间，无数火红的石块带着火焰坠落下来时却变成了巨大的火\n"
"球，伴随着巨大的声响，地动山摇，令人惊魂难定。\n"
);
        set("exits", ([ 
                "north"   : __DIR__"huoyangu",
                "south"   : __DIR__"liehuoxiagu",
        ]));
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/jinsefenghuang");
        
        setup();
}
