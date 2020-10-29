
inherit "/inherit/room/house_base";

void create()
{
    set("short", "海岸");
    set("long", @LONG
这里是海港外十许里的海滩，倒也静谧。极目远望，但见点点白
帆若隐若现。细碎的浪花拍打着沙地，哗哗作响。滩外一箭之地，有
一处大院落，似乎是江湖中哪个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "north"  : "/clone/room/matou/dg",
    ]));

    set("outdoors", "beijing");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
