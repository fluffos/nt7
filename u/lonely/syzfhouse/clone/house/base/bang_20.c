
inherit "/inherit/room/house_base";

void create()
{
    set("short", "军镇外");
    set("long", @LONG
这里是军镇外的荒原空地，地上寥落长着些灌木枯草。不远处列
一排高大挺立的白桦树。在阵阵北风中，仿佛能听见枝头枯叶沙沙作
响。白桦树后现出一座大宅院，俨然是江湖中哪个帮会的驻地。
LONG);

    set("exits",
    ([
        "east"  : "/d/shanhai-guan/junzheng",
    ]));

    set("outdoors", "shanhai-guan");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
