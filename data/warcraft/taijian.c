// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿衰[2;37;0m[2;37;0m", ({"sxs"}));        
        set("gender", "女性");                
        set("long", "搜索[2;37;0m
它是葵花太监的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "taijian");
        set("owner_name", "葵花太监");
        set_temp("owner", "taijian");
        set_temp("owner_name", "葵花太监");
        ::setup();
}
