inherit __DIR__"binghuodao";

void create()
{
        set("short", "烈火峡～谷");
        set("long",
"来到这里，已经很难用辞藻来形容这里的异象，天空中火光闪\n"
"耀，电闪雷鸣，不时又遮天蔽日，定睛一看，竟然是一条巨大火龙，\n"
"喷吐着火焰。火龙飞过，无数如流星雨般的火石从天而下……\n"
);
        set("exits", ([ 
                "north"   : __DIR__"huoyanshiqiao",
        ]));
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/huolong");
        
        setup();
}
