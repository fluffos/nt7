inherit __DIR__"binghuodao";

void create()
{
        set("short", "圣火台");
        set("long",
"这里是一处宽阔的祭台，祭台中间有一根石柱，上面写着鲜红\n"
"的三个大字“升火台”，祭台四周矗立着四根石柱，上面雕刻着各种\n"
"奇怪的模样。据说在这里研究技能可获得更多研究次数。\n"
);
        set("exits", ([ 
                "north"   : __DIR__"jitan", 
                "south"   : __DIR__"shenmihuodong",
                "west"    : __DIR__"huoyangu2",
        ]));
        setup();
}
