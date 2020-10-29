inherit ROOM;

void create()
{
        set("short", "梳妆台");
        set("long", @LONG
藏经殿有一泓碧泉如镜，向称美容泉。相传为南陈后主妃在此避
乱时，对碧水照容颜梳妆打扮的地方。殿前胜迹有灵日，昔时夜间常
见飞光，或如繁星点点，或若万萤乱飞，煞是壮观。
LONG );
        set("exits", ([ 
               "north"   : __DIR__"cangjingdian",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6960);
	set("coor/y", -5520);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}