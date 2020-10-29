// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("碧水晶晶兽[2;37;0m[2;37;0m", ({"dafang"}));        
        set("gender", "女性");                
        set("long", "finish[2;37;0m
它是渡蛋蛋的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fzm");
        set("owner_name", "渡蛋蛋");
        set_temp("owner", "fzm");
        set_temp("owner_name", "渡蛋蛋");
        ::setup();
}
