// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"das"}));        
        set("gender", "女性");                
        set("long", "sd[2;37;0m
它是易曲的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yiqu");
        set("owner_name", "易曲");
        set_temp("owner", "yiqu");
        set_temp("owner_name", "易曲");
        ::setup();
}
