// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m玲珑雀[2;37;0m[2;37;0m[2;37;0m", ({"meccypet"}));        
        set("gender", "女性");                
        set("long", "啊是[2;37;0m
它是阿兰千夜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "meccy");
        set("owner_name", "阿兰千夜");
        set_temp("owner", "meccy");
        set_temp("owner_name", "阿兰千夜");
        ::setup();
}
