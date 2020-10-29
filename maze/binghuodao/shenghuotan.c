inherit __DIR__"binghuodao";

void create()
{
        set("short", "神火坛");
        set("long",
"这里是一处宽阔的祭台，祭台中间有一根石柱，上面写着鲜红\n"
"的三个大字“神火台”，祭台四周矗立着四根石柱，上面雕刻着各种\n"
"火焰的模样。据说在这里汲取实战体会（jiqu）能获得更多收获。\n"
);
        set("exits", ([ 
                "east"   : __DIR__"guanmulin2", 
                "southwest"   : __DIR__"shenmihuodong2",
        ]));
        setup();
}
