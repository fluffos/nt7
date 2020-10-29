// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小白[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "女性");                
        set("long", "长着两只兔子耳朵的小动物[2;37;0m
它是字谁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "warrier");
        set("owner_name", "字谁");
        set_temp("owner", "warrier");
        set_temp("owner_name", "字谁");
        ::setup();
}
