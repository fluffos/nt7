
inherit "/inherit/room/house_base";

void create()
{
    set("short", "山谷");
    set("long", @LONG
这是垭口内侧的狭小山谷，两边岩壁怪石嶙峋，鲜有植被。远处
昆仑山脉绵延千里，群山起伏，峰顶白雪皑皑终年不化。东面山坡上
依山而建一座大院，看来好像是江湖中哪个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "east"  : "/d/kunlun/kunlun-shankou",
    ]));

    set("outdoors", "kunlun");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
