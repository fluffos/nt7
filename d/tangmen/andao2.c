//andao2.c                四川唐门—地道

inherit ROOM;

void create()
{
        set("short","地道");
        set("long",
"这里,四周漆黑一团,你好象什么都看不见似的走在里面,你不觉想到\n"
"这似乎在每个角落都藏着无限杀机,太恐怖了四周毫无声息，好象掉下一\n"
"根针都可能听到。\n"
);
        set("exits",([
                "north" : __DIR__"andao1",
                "west" : __DIR__"huayuan",
        ]));
        setup();
        replace_program(ROOM);
}