inherit DEMONROOM;

void create()
{
        set("short", "寒冰洞外");
        set("long",@LONG
这里是神龙岛一处隐秘的洞穴，此处略觉寒冷，据说洞内藏有各种怪兽，
传说一只巨大的冰龙就住在这洞内，但是没人见过。。
LONG);

	set("exits", ([
		"east"   : __DIR__"dong1.17",
                //"enter"   : __DIR__"bingdong1",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 3);
		set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
