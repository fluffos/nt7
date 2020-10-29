// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小笨瓜[2;37;0m[2;37;0m", ({"unitwang"}));        
        set("gender", "女性");                
        set("long", "呆呆傻傻[2;37;0m
它是冷夜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "unit");
        set("owner_name", "冷夜");
        set_temp("owner", "unit");
        set_temp("owner_name", "冷夜");
        ::setup();
}
