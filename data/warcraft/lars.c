// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("拉哥[2;37;0m[2;37;0m", ({"larko"}));        
        set("gender", "女性");                
        set("long", "拉哥[2;37;0m
它是拉斯拉的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lars");
        set("owner_name", "拉斯拉");
        set_temp("owner", "lars");
        set_temp("owner_name", "拉斯拉");
        ::setup();
}
