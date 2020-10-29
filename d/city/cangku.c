// Room: /city/cangku.c

inherit ROOM;
void init();

void create()
{
	set("short", "仓库");
        set("long", @LONG
这里是一间黑黝黝的仓库，堆满了唐家的各种杂物，塞了满满一
仓库。看来你是被人拐卖到这里来的。
LONG );
	set("valid_startroom", "1");
	set("no_fight", 1);
//	set("no_clean_up", 0);

	set("objects", ([
		"/d/city/obj/jitui" : 3,
		"/d/city/obj/jiudai" : 1,
	]));
	setup();
}

void init()
{
	object ob;

	ob = this_player();
set("startroom", "/d/city/cangku", 	ob);
set_temp("selled", 1, 	ob);
}