inherit ROOM;

void create()
{
        set("short", "松林");
        set("long", @LONG
这是松林深处，暗无天日，朦胧中只感觉到左右前后到处都是树
影。地上有一两个死人骷髅，发着绿荧荧的磷光。你惊骇之间，一脚
踩在钢针般的松针上！
LONG );
        set("outdoors", "wudang");
        set("exits",([
                "north" : __DIR__"songlin4",
                "south" : __DIR__"slxl2",
        ]));
        set("coor/x", -340);
        set("coor/y", -170);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}