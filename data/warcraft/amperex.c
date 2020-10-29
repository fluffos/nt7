// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m谛听[2;37;0m[2;37;0m", ({"listen"}));        
        set("gender", "男性");                
        set("long", "辨识世间万物本质,透视众生灵魂,免疫一切忽悠！！！[2;37;0m
它是素还真的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "amperex");
        set("owner_name", "素还真");
        set_temp("owner", "amperex");
        set_temp("owner_name", "素还真");
        ::setup();
}
