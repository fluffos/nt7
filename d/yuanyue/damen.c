// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "圆月山庄大门");
        set("long", @LONG
路到尽头，便是闻名天下的『圆月山庄』的大门。乍一望去，大
门梁上雕龙刻凤，美奂美仑，不知凝聚着多少能工巧匠的心血。不禁
让人以为庄主定是富有显贵之人。门前左右各蹲着一只威武庄严的石
狮子。但定睛细瞧，则让人喟叹不己，原来门上锈迹斑斑，满是灰尘，
红漆也已剥落大半，莫名之中让人产生一种凄凉的感觉。
LONG );
        set("outdoors", "yuanyue");
        set("type", "street");
        set("exits",([
                "south":__DIR__"shandao2",
                "enter":__DIR__"suishilu1",
        ]) );

        set("coor/x",-590);
        set("coor/y",200);
        set("coor/z",80);
        
        setup();
        
        replace_program(ROOM);
} 
