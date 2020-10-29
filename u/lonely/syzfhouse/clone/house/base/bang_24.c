
inherit "/inherit/room/house_base";

void create()
{
    set("short", "青石坪");
    set("long", @LONG
这里是上山路侧的一处平台，由平坦的大小青石拼凑而成。石间
挺立三四株翠柏，树下偶尔会有歇脚的进香客人。一条清澈见底的小
溪从坪前绕过，静静横在坪后的宏大庄院门前，看来似是江湖中某个
帮会的驻地所在。
LONG);

    set("exits",
    ([
        "north"  : "/d/emei/qing-shijie1",
    ]));

    set("outdoors", "emei");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
