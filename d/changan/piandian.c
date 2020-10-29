//Room: piandian.c

inherit ROOM;

void create ()
{
  set ("short", "偏殿");
        set("long", @LONG
偏殿里气氛宁静，灵台高筑，依次摆列着八菩萨的佛象。这里香
火也是不断，地上铺着一些蒲团。但见南面两侧一动也不动地盘坐著
两名枯瘦的老僧，左首那僧脸色通红，左手捏个拈花抉，右手合指朝
天；右首那僧却脸色青绿，右手捏著拈花抉，左手合指朝天。二僧姿
式一模一样，却偏生左右相反。东边殿门通向大雄宝殿，
LONG );

        set("exits", ([
                "east"    : "/d/changan/baodian",
        ]));

        set("objects", ([
                "/d/changan/npc/jingxuan" : 1,
                "/d/changan/npc/jingming" : 1,
        ]));

        set("coor/x", -10740);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}