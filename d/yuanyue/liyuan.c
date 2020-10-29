// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "梨园"); 
        set("long", @LONG
这里便是圆月山庄的『圣地』梨园，之所以这样说，因为对柳若
松他来说，这儿不仅意味着饿了可以拿几只梨子充饥，更加重要的是，
酒虫上来了，也能摘几筐梨拿去换酒喝，时已深秋，梨树上原本还有
满树又甜又大的梨子，但现在却已经被摘得几乎所剩无几了。
LONG );
        set("type","forest");
        set("outdoors", "wansong");
        set("exits",([
                "west":__DIR__"shibanlu2",
        ]) );

        set("objects",([
                CLASS_D("mojiao/yinlong") : 1,
        ]) );
        
        set("coor/x",-570);
        set("coor/y",220);
        set("coor/z",80);
        setup(); 
} 
