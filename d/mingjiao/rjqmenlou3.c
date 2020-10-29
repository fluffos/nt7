//RJQMENLOU3.C

inherit ROOM;

void create()
{
        set("short", "门楼三层");
        set("long", @LONG
这里是一间大石室，中央摆放着石桌(zhuo)石椅(chair)，石桌上
刻有纵横交错的图案，仔细看，原来是一棋局，棋盘上两黑(heizi)、
一白(bai zi)，正该白方落子了。却不知对弈的棋士为何没有下完。
LONG );
        set("exits", ([
                "down" : __DIR__"rjqmenlou2",
        ]));
        setup();
}

void init()
{
        add_action("do_push", "push");
        add_action("do_sit", "sit");
}

int do_sit(string arg)
{

        if (arg != "chair")
                return notify_fail("你一下坐了个屁股墩。\n");

        if( query_temp("allsit", this_player()) == 1 )
                return notify_fail("你已经坐下了。\n");

        set_temp("allsit", 1, this_player());
        return notify_fail("你找了个空椅子座下，开始思考棋局。\n");
}

int do_push(string arg)
{
        object me;

        me = this_player();
        if (query_temp("allsit", me) != 1)
        {
                message_vision("$N只觉得一阵恍惚，倒在了地上。\n", me);
                delete_temp("hei", me);
                delete_temp("allsit", me);
                me->unconcious();
                return 1;
        }

        if (arg != "hei zi" && arg != "bai zi")
                return notify_fail("你轻轻按了一下石桌，真是一块好玉呀！\n");

        if( query_temp("allsit", me) && (arg == "heizi") )
        {
                if (query_temp("hei", me)==2)
                {
                        delete_temp("hei", me);
                        write("你轻轻按了一下黑棋子，什么反应也没有。\n");
                        return 1;
                } else
                if (query_temp("hei", me)==1)
                {
                        set_temp("hei", 2, me);
                        write("你轻轻按了一下黑棋子，什么反应也没有。\n");
                        return 1;
                } else
                if (query_temp("hei", me)==0)
                {
                        set_temp("hei", 1, me);
                        write("你轻轻按了一下黑棋子，什么反应也没有。\n");
                        return 1;
                }
        }

        if (query_temp("allsit", me) && (arg=="bai zi"))
        {
                if(query_temp("hei", me)==2)
                {
                        message_vision("只见石椅猛的一沉，$N一声惨叫，直"
                                       "跌到洞中去了。\n", me);
                        delete_temp("hei", me);
                        delete_temp("allsit", me);
                        me->move(__DIR__"rjqmidao");
                        return 1;
                }
                else
                {
                        write("你轻轻按了一下白棋子，什么反应也没有。\n");
                        return 1;
                }
        }
}

int valid_leave(object me, string dir)
{
            delete_temp("hei", me);
            delete_temp("allsit", me);
            return ::valid_leave(me, dir);
}
