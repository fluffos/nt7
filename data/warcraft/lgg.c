// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗故事[2;37;0m[2;37;0m", ({"lggs"}));        
        set("gender", "女性");                
        set("long", "哈哈[2;37;0m
它是老狗柒的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lgg");
        set("owner_name", "老狗柒");
        set_temp("owner", "lgg");
        set_temp("owner_name", "老狗柒");
        ::setup();
}
