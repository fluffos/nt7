// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "神秘的火麒麟[2;37;0m
它是紫莲的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zilian");
        set("owner_name", "紫莲");
        set_temp("owner", "zilian");
        set_temp("owner_name", "紫莲");
        ::setup();
}
