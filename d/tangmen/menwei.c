//menwei.c                四川唐门—差房

inherit ROOM;

void create()
{
        set("short", "差房");
        set("long",
"这里是莲藕小筑的差房。平常唐门的下人们都喜欢聚在这里比较各自\n"
"主人的武功高低，不过可不要小瞧这些下人，其中也不乏高手。这里往东\n"
"是亭榭水阁。\n"
);
        set("exits", ([        "east" : __DIR__"shuige1",]));
        set("objects", ([__DIR__"npc/menwei" : 2,]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}