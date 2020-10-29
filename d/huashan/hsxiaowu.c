inherit ROOM;

void create()
{
    set("short", "后山小屋");
        set("long", @LONG
后山小屋是华山两位长老的避世居所。摆设简单，却清雅自然。
小屋外有个小池塘，几只鹤有的在池塘边飞舞，有的站在池塘边歇息。
两位长老不喜欢外人打扰，当今华山掌门也甚少到访。
LONG );

    set("exits", ([
        "southdown" : __DIR__"chaopath2",
    ]));

    set("objects", ([
        CLASS_D("huashan") + "/gao-laozhe" : 1,
        CLASS_D("huashan") + "/ai-laozhe" : 1,
    ]));

    set("no_clean_up", 0);

    setup();
    replace_program(ROOM);
}
