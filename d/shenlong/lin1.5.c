inherit DEMONROOM;

void create()
{
        set("short", "东灌木林");
        set("long",@LONG
这是一片灌木林。你没有想到这样一个孤岛上竟有这样大一片灌
木林，不由感到非常吃惊。
LONG);

	set("exits", ([
		"east"  : __DIR__"lin1.6", 
		"west"  : __DIR__"lin1.4",

	]));


		
		set("n_time", 30); 
		set("n_npc", 3); 
		set("n_max_npc", 20);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/jinshe");

        set("outdoors", "shenlong");
        setup();
}
