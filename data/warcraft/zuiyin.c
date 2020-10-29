// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("诗意天城[2;37;0m[2;37;0m", ({"shiyi"}));        
        set("gender", "男性");                
        set("long", "单刀残躯饮寒风，今朝有酒醉黄龙。[2;37;0m
它是醉饮黄龙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zuiyin");
        set("owner_name", "醉饮黄龙");
        set_temp("owner", "zuiyin");
        set_temp("owner_name", "醉饮黄龙");
        ::setup();
}
