inherit BUILD_ROOM;

void create()
{
        set("short", "老龙头");
        set("long", @LONG
老龙头是万里长城最东端。澄海楼巍峨高踞城头，楼上“雄襟万里”的
横匾居高临下，直俯大海。自澄海楼筑有一石城逐级而下伸入大海，站在石
城终端楼平台上四眺，海天一色，无边无际，气象万千。
LONG );
        set("exits", ([
                "northwest" : __DIR__"shanhaiguan",
                "southwest" : "/d/beijing/road3",
        ]));

        set("outdoors", "guanwai");
        set("coor/x", 3950);
	set("coor/y", 9110);
	set("coor/z", 0);
	setup();
}
