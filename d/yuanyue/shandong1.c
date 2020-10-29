inherit ROOM;
void create()
{
        set("short", "金冠巨蟒洞"); 
        set("long", @LONG
爬了许久，洞道渐宽，到了此处，便豁然开朗，已可站直身躯。
你定睛一瞧，不禁大惊失色，洞中霍然有条长达数丈，粗若水桶的金
冠巨蟒盘旋其中，一对碧眼如炬，烁然放光。洞中骸骨遍地，腥臭异
常，积满秽物。
LONG );
        set("indoors", "wansong");
        set("type","mountain");
        set("exits",([
                "south":__DIR__"shandong",
        ]) );
        set("objects", ([
                "/clone/beast/xuanmang" : 1,
                __DIR__"obj/skeleton" : 2,
        ]) ); 
        set("coor/x",-610);
        set("coor/y",300);
        set("coor/z",80);
        set("refresh_all_items", 1);
        setup();
} 
