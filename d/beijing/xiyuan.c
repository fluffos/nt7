inherit ROOM;

void create()
{
        set("short", "长安戏院");
        set("long", @LONG
这里就是京城里著名的长安戏院，是京城百姓休息和娱乐的佳所。
戏台上面几个戏子正在唱戏。台下黑压压的一片都是人。唱到妙处，
台下的观众们禁不住大声喝采。北边一条小道通往戏院的后台。
LONG );
        set("exits", ([
                "north" : __DIR__"xiyuanup",
                "west"   : __DIR__"wang_10",
        ]));
        set("objects", ([
                __DIR__"npc/guanzhong" : 3,
                __DIR__"npc/xianren" : 1,
                __DIR__"npc/jumin1" : 1,
        ]));
        

	set("coor/x", -2760);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && userp(me))
        {               
                message_vision(  
                        "只听哗啦啦一片掌声，观众们一起鼓掌。有人大声说道："
                        "净一净，请看这位" + RANK_D->query_respect(me)+ "表演。\n",
                        this_player());
                return ::valid_leave(me, dir);
        }
        else return 1;
}