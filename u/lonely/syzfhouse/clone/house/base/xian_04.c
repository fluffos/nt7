//蓬莱、瀛洲、方壶、员峤、岱舆
inherit "/inherit/room/house_base";

void create()
{
    set("short", "小员峤");
    set("long", @LONG
此地景致幽雅异常，放眼望去，但见柏苍松翠，瑶草芊芊，奇花
争妍，流水深深，云生岭上，风飒林间。林中有寿鹿仙狐出没，树上
灵禽玄鹤翩跹。远处亭台楼阁隐现，幽幽仙籁时闻，寂然不见人迹。
LONG);

    set("exits",
    ([
        "east" : "/d/city/sanxian-zhuang",
    ]));

    set("outdoors", "city");
    set("max_build", 2);
    set("can_build", "xian");

    setup();
    restore();
}
