inherit ROOM;
void create()
{
        set("short", "山谷口");
        set("long",
"路边立着一块石碑，上面写着两个古篆字：甘凉。往山谷看去，一条\n"
"弯弯曲曲的小路伸向谷内，一危崖从中断开。\n"
);
        set("exits", ([
            "out" : "/d/kunlun/shankou",
           "westup": __DIR__"road1",
]));
        set("outdoors","llszhuang");
        setup();
}
