inherit ROOM;

void create()
{
        set("short", "松林小路");
        set("long", @LONG
这是山脚松林中的小路，两边长满参天的红松树，只能看见一线
天空。路旁有道士在奋力砍树。西边通向密林深处，东边可回大道。
LONG );
        set("outdoors", "wudang");
        set("exits", ([
                "west" : __DIR__"slxl2",
                "east" : __DIR__"wdroad10",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -330);
        set("coor/y", -180);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}