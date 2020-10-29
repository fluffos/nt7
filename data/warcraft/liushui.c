// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎妹[2;37;0m[2;37;0m", ({"humei"}));        
        set("gender", "女性");                
        set("long", "嘿嘿，白虎难得呀，你懂的！！！！[2;37;0m
它是水流的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "liushui");
        set("owner_name", "水流");
        set_temp("owner", "liushui");
        set_temp("owner_name", "水流");
        ::setup();
}
