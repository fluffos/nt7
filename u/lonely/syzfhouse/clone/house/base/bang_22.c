
inherit "/inherit/room/house_base";

void create()
{
    set("short", "嘉峪关东");
    set("long", @LONG
这是嘉峪关东首的黄土山丘。低矮的灌木四处散布，倒也长得有
些葱茏。站在此处西望，嘉峪关关城楼阁高耸，巍峨壮观。再往东去
几步是一座恢宏的庄院，看似江湖中哪个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "west"  : "/d/xiyu/jiayu-guan",
    ]));

    set("outdoors", "xiyu");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
