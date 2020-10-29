inherit __DIR__"binghuodao";

void create()
{
        set("short", "玄武台");
        set("long",
"这里是一处宽阔的祭台，祭台中间有一根石柱，上面写着鲜红\n"
"的三个大字“玄武台”，祭台四周矗立着四根石柱，上面雕刻着玄武\n"
"神兽的模样。据说在这里冥思（reflect）能获得更多收获。\n"
);
        set("exits", ([ 
                "west"   : __DIR__"bingfenggu2", 
                "north"   : __DIR__"shenmibingdong",
                "south"   : __DIR__"jitan",
        ]));
        setup();
}
