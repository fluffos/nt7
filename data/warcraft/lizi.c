// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("叶子[2;37;0m[2;37;0m", ({"yezi"}));        
        set("gender", "女性");                
        set("long", "绿色的叶子[2;37;0m
它是梨子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lizi");
        set("owner_name", "梨子");
        set_temp("owner", "lizi");
        set_temp("owner_name", "梨子");
        ::setup();
}
