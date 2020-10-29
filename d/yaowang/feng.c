inherit ROOM;

void create()
{
        set("short", "山峰");
        set("long", @LONG
这里是一处光秃秃的山峰，由南面向下望去，气势恢宏的药王谷
尽收眼底，边上十几丈高的陡峭石壁。西面有一块石头绞盘，
盘上拴着一根胳膊粗的[绳子]垂向下面。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "southdown" : __DIR__"shangpo5",
]));

        set("item_desc", ([
        "绳子" : "这是一根胳膊粗绳子，看样子是攀(climb)着上下山峰用的。\n",
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

        if(find_call_out("arrive_down") != -1)
                return notify_fail("有人正在攀着绳子向下爬呢，等一会儿。\n");

        me->start_busy(3);
        message_vision("$N攀着绳子缓缓的向下爬去。\n", me);
        call_out("arrive_down", 2, me);

        return 1;
}

protected void arrive_down(object who)
{
        if(!who || (environment(who) != this_object()))
                return;

        who->move(__DIR__"fengdown1");
}
