//ROOM: hua1.c

inherit ROOM;

void create()
{
        set("short", "花园");
        set("long", @LONG
这是一个极精致的小花园。园中，红梅绿竹，青松翠柏，布置得
颇具匠心，往西去是一片青草地。
LONG );
        set("exits", ([
            "west" : __DIR__"grass2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}