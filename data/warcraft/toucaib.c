// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m蹲坑居士[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "蹲坑居士[2;37;0m
它是二号菜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "toucaib");
        set("owner_name", "二号菜");
        set_temp("owner", "toucaib");
        set_temp("owner_name", "二号菜");
        ::setup();
}
