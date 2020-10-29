inherit ROOM;

void create()
{
        set("short", "天蚕洞");
        set("long", @LONG
这里是天山蚕洞，只见洞内非常宽敞，洞顶可看见蓝天白
云，听说这里是天蚕繁殖的地方。

LONG);
        set("exits", ([
                "out" : __DIR__"tianroad6",
        ]));
        set("outdoors", "xingxiu");
        // 可打猎标志
        set("can_hunting", 1);
        set("quarry", ([
             "can"       :  20,
             "tiancan"   :  50,
             "zhang"     :  40,
        ]));

        setup();
}

