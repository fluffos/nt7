//chashi.c                四川唐门—茶室

inherit ROOM;

void create()
{
        set("short", "茶室");
        set("long",
"这里是莲藕小筑的茶室。通常唐门弟子都喜欢在这里谈天说地，交流\n"
"各自的武功进展，也时常谈论一些江湖中恩恩怨怨，从这里往西是亭榭水阁。\n"
);
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("item_desc", ([
                "paizi" : "楼上雅房，每夜五十两白银。\n",
        ]));
        set("exits", ([        
                        "west" : __DIR__"shuige1",
        ]));
        set("area", "蜀中亭榭水阁");
        setup();
        "/clone/board/tangmen_b"->foo(); 
        replace_program(ROOM);
}