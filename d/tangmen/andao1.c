//andao1.c                四川唐门—地道

inherit ROOM;

void create()
{
        set("short","地道");
        set("long",
"这是一条地道。一进入这里四周突然变的漆黑一团，你什么都看不见\n"
"，走在里面你总觉得有无数双眼睛在盯着你看，但是四周又毫无声息，好\n"
"象掉下一根针都可能听到。北边隐隐又一丝光亮传来。\n"
);
        set("exits",([
                "south" : __DIR__"andao2",
                "north" : __DIR__"didao4",
        ]));
        setup();
        replace_program(ROOM);
}