// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m蹲坑居士[2;37;0m[2;37;0m", ({"dkjs"}));        
        set("gender", "男性");                
        set("long", "蹲坑居士 -- 小救星[2;37;0m
它是一号菜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "toucaia");
        set("owner_name", "一号菜");
        set_temp("owner", "toucaia");
        set_temp("owner_name", "一号菜");
        ::setup();
}
