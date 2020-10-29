inherit __DIR__"binghuodao";

void create()
{
        set("short", "神冰坛");
        set("long",
"这里是一处宽阔的祭台，祭台中间有一根石柱，上面写着蓝色\n"
"的三个大字“神冰台”，祭台四周矗立着四根石柱，上面雕刻着各种\n"
"冰兽的模样。据说在这里研究技能（yanjiu）能获得更多收获。\n"
);
        set("exits", ([ 
                "east"   : __DIR__"guanmulin1", 
                "northwest"   : __DIR__"shenmibingdong2",
        ]));
        setup();
}
