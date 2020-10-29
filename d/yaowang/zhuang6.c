inherit __DIR__"zhuang";

void create()
{
        set("short", "梅花桩一");
        set("long", @LONG
一人多高的梅花桩，向下望去真让人心惊胆颤。
LONG
        );

        set("exits", ([
        "down" : __DIR__"lianwu",
        "west" : __DIR__"zhuang5",
]));
        setup();
}

int valid_leave(object ob,string dir)
{
        int sk;

        if(dir == "down")
        {
                if(sk = ob->query_skill("dodge", 1) < 80)
                        ob->improve_skill("dodge", sk+10);
                if( query("combat_exp", ob)<100000 )
                        addn("combat_exp", 20+random(20), ob);
        }

        return 1;
}
