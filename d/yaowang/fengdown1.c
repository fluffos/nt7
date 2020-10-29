inherit ROOM;

void create()
{
        set("short", "山崖下");
        set("long", @LONG
这里是山谷的谷底，静悄悄地没有一点声响。西面是陡峭的
山壁高耸入云，山壁下面有一根胳膊粗的[绳子]从上面垂下来。
LONG
        );

        set("item_desc", ([
        "绳子" : "这是一根胳膊粗绳子，看样子是攀(climb)着上下山峰用的。\n",
]));

        set("exits", ([
        "west" : __DIR__"fengdown2",
]));

        set("outdoors", "yaowang");
        setup();
}

void init()
{
        add_action("do_push", "climb");
}

int do_push(string arg)
{
        object me = this_player();

        if(arg != "绳子")
                return 0;

        if(find_call_out("arrive_up") != -1)
                return notify_fail("有人正在攀着绳子向上爬呢，等一会儿。\n");

        me->start_busy(3);
        message_vision("$N攀着绳子缓缓的向上爬去。\n", me);
        call_out("arrive_up", 2, me);

        return 1;
}

protected void arrive_up(object who)
{
        if(!who || (environment(who) != this_object()))
                return;

        who->move(__DIR__"feng");
}
