// Room: /d/ruzhou/yamen-datang.c
// llm 1999/07/04

inherit ROOM;

void create()
{
        set("short", "知府大堂");
        set("long", @LONG
正中一面明镜高悬的大匾，是各地的衙门必备的家当。大堂的地上擦得逞亮却
隐约能看到一点点的血痕，看来是大堂用刑时留下的痕迹。两边各各一些肃静、回
避的牌子，竟有些不威自怒的感觉。
LONG
        );
        set("exits", ([
           "south" : __DIR__"yamen-damen",
        ]));
        set("objects", ([
                __DIR__"npc/jiang-yaoting":1,
      __DIR__"npc/yayi":4,
        ]));
        set("no_fight", 1);

	set("coor/x", -6770);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
